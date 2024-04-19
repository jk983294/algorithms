#ifndef DISRUPTOR_WAIT_STRATEGY_H_
#define DISRUPTOR_WAIT_STRATEGY_H_

#include <sys/time.h>

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

#include "Sequence.h"

namespace disruptor {

/**
 * Strategy employed for a Consumer to wait on the sequencer's cursor and a set of consumers' Sequences.
 */

/**
 * Busy Spin strategy that uses a busy spin loop waiting on a barrier.
 * This strategy will use CPU resource to avoid syscalls which can introduce latency jitter.
 * It is strongly recommended to pin threads on isolated CPU cores to minimize context switching and latency.
 */
class BusySpinStrategy;

/**
 * Yielding strategy that uses a thread::yield() for waiting on a barrier.
 * This strategy is a good compromise between performance and CPU resource.
 * @tparam S RetryLoops
 */
template <int64_t S>
class YieldingStrategy;

/**
 * Sleeping strategy uses a progressive back off strategy by first spinning for S/2 loops,
 * then yielding for S/2 loops, and finally sleeping for duration<D, DV> until ready to advance.
 * This is a good strategy for burst traffic then quiet periods when latency is not critical.
 * @tparam S RetryLoops
 * @tparam D Duration
 * @tparam DV DurationValue
 */
template <int64_t S, typename D, int DV>
class SleepingStrategy;

/**
 * Blocking strategy that waits for the sequencer's cursor to advance on the requested sequence.
 * The sequencer MUST call SignalAllWhenBlocking() to unblock the strategy when waiting on the cursor.
 * Once the cursor is advanced, the strategy will busy spin on the dependents' sequences
 * and can be cancelled by affecting the `alerted` atomic.
 *
 * The user can optionally provide a maximum timeout to the blocking operation,
 * see std::condition_any::wait_for() documentation for limitations.
 *
 * This strategy uses a condition variable inside a lock to block the event processor
 * which saves CPU resource at the expense of lock contention.
 * Publishers must explicitly call SignalAllWhenBlocking() to unblock consumers.
 * This strategy should be used when performance and low-latency are not as important as CPU resource.
 */
class BlockingStrategy;

// defaults
using DefaultWaitStrategy = BusySpinStrategy;
constexpr int64_t DefaultRetryLoops = 200L;
using DefaultDuration = std::chrono::milliseconds;
constexpr int DefaultDurationValue = 1;

// used internally
static inline std::function<int64_t()> buildMinSequenceFunction(const Sequence& cursor,
                                                                const std::vector<Sequence*>& dependents);

class BusySpinStrategy {
public:
    BusySpinStrategy() {}

    /**
     * Wait for the given sequence to be available for consumption
     * @param sequence to wait for
     * @param cursor sequencer's cursor
     * @param dependents
     * @param alerted indicator of consumer alert
     * @return AlertedSignal if the barrier signaled an alert,
     *         otherwise return the greatest available sequence which may be greater than requested
     */
    int64_t WaitFor(const int64_t& sequence, const Sequence& cursor, const std::vector<Sequence*>& dependents,
                    const std::atomic<bool>& alerted) {
        int64_t availableSequence = InitialCursorValue;
        const auto min_sequence_func = buildMinSequenceFunction(cursor, dependents);

        while ((availableSequence = min_sequence_func()) < sequence) {
            if (alerted.load()) return AlertedSignal;
        }

        return availableSequence;
    }

    template <class R, class P>
    int64_t WaitFor(const int64_t& sequence, const Sequence& cursor, const std::vector<Sequence*>& dependents,
                    const std::atomic<bool>& alerted, const std::chrono::duration<R, P>& timeout) {
        int64_t availableSequence = InitialCursorValue;

        const auto start = std::chrono::system_clock::now();
        const auto stop = start + timeout;
        const auto min_sequence_func = buildMinSequenceFunction(cursor, dependents);

        while ((availableSequence = min_sequence_func()) < sequence) {
            if (alerted.load()) return AlertedSignal;

            if (stop <= std::chrono::system_clock::now()) return TimeoutSignal;
        }

        return availableSequence;
    }

    /**
     * Signal the strategy that the cursor as advanced. Some strategy depends on this behaviour to unblock.
     */
    virtual void SignalAllWhenBlocking() {}

    DISALLOW_COPY_MOVE_AND_ASSIGN(BusySpinStrategy);
};

template <int64_t S = DefaultRetryLoops>
class YieldingStrategy {
public:
    YieldingStrategy() {}

    int64_t WaitFor(const int64_t& sequence, const Sequence& cursor, const std::vector<Sequence*>& dependents,
                    const std::atomic<bool>& alerted) {
        int64_t availableSequence = InitialCursorValue;
        int retryCounter = S;

        const auto min_sequence_func = buildMinSequenceFunction(cursor, dependents);

        while ((availableSequence = min_sequence_func()) < sequence) {
            if (alerted.load()) return AlertedSignal;
            retryCounter = ApplyWaitMethod(retryCounter);
        }

        return availableSequence;
    }

    template <class R, class P>
    int64_t WaitFor(const int64_t& sequence, const Sequence& cursor, const std::vector<Sequence*>& dependents,
                    const std::atomic<bool>& alerted, const std::chrono::duration<R, P>& timeout) {
        int64_t availableSequence = InitialCursorValue;
        int64_t retryCounter = S;

        const auto start = std::chrono::system_clock::now();
        const auto stop = start + timeout;
        const auto min_sequence_func = buildMinSequenceFunction(cursor, dependents);

        while ((availableSequence = min_sequence_func()) < sequence) {
            if (alerted.load()) return AlertedSignal;

            retryCounter = ApplyWaitMethod(retryCounter);
            if (stop <= std::chrono::system_clock::now()) return TimeoutSignal;
        }
        return availableSequence;
    }

    virtual void SignalAllWhenBlocking() {}

private:
    inline int64_t ApplyWaitMethod(int64_t retryCounter) {
        if (retryCounter) {
            return --retryCounter;
        }

        std::this_thread::yield();
        return retryCounter;
    }

    DISALLOW_COPY_MOVE_AND_ASSIGN(YieldingStrategy);
};

template <int64_t S = DefaultRetryLoops, typename D = DefaultDuration, int DV = DefaultDurationValue>
class SleepingStrategy {
public:
    SleepingStrategy() {}

    int64_t WaitFor(const int64_t& sequence, const Sequence& cursor, const std::vector<Sequence*>& dependents,
                    const std::atomic<bool>& alerted) {
        int64_t availableSequence = InitialCursorValue;
        int retryCounter = S;

        const auto min_sequence_func = buildMinSequenceFunction(cursor, dependents);

        while ((availableSequence = min_sequence_func()) < sequence) {
            if (alerted.load()) return AlertedSignal;

            retryCounter = ApplyWaitMethod(retryCounter);
        }
        return availableSequence;
    }

    template <class R, class P>
    int64_t WaitFor(const int64_t& sequence, const Sequence& cursor, const std::vector<Sequence*>& dependents,
                    const std::atomic<bool>& alerted, const std::chrono::duration<R, P>& timeout) {
        int64_t availableSequence = InitialCursorValue;
        int64_t retryCounter = S;

        const auto start = std::chrono::system_clock::now();
        const auto stop = start + timeout;
        const auto min_sequence_func = buildMinSequenceFunction(cursor, dependents);

        while ((availableSequence = min_sequence_func()) < sequence) {
            if (alerted.load()) return AlertedSignal;

            retryCounter = ApplyWaitMethod(retryCounter);
            if (stop <= std::chrono::system_clock::now()) return TimeoutSignal;
        }

        return availableSequence;
    }

    void SignalAllWhenBlocking() {}

private:
    inline int64_t ApplyWaitMethod(int64_t retryCounter) {
        if (retryCounter > (S / 2)) {
            --retryCounter;
        } else if (retryCounter > 0) {
            --retryCounter;
            std::this_thread::yield();
        } else {
            std::this_thread::sleep_for(D(DV));
        }
        return retryCounter;
    }

    DISALLOW_COPY_MOVE_AND_ASSIGN(SleepingStrategy);
};

class BlockingStrategy {
public:
    BlockingStrategy() {}

    int64_t WaitFor(const int64_t& sequence, const Sequence& cursor, const std::vector<Sequence*>& dependents,
                    const std::atomic<bool>& alerted) {
        return WaitFor(sequence, cursor, dependents, alerted, [this](Lock& lock) {
            consumerNotifyCondition.wait(lock);
            return false;
        });
    }

    template <class Rep, class Period>
    int64_t WaitFor(const int64_t& sequence, const Sequence& cursor, const std::vector<Sequence*>& dependents,
                    const std::atomic<bool>& alerted, const std::chrono::duration<Rep, Period>& timeout) {
        return WaitFor(sequence, cursor, dependents, alerted, [this, timeout](Lock& lock) {
            return std::cv_status::timeout ==
                   consumerNotifyCondition.wait_for(lock, std::chrono::microseconds(timeout));
        });
    }

    void SignalAllWhenBlocking() {
        std::unique_lock<std::recursive_mutex> ulock(mtx);
        consumerNotifyCondition.notify_all();
    }

private:
    using Lock = std::unique_lock<std::recursive_mutex>;
    using Waiter = std::function<bool(Lock&)>;

    inline int64_t WaitFor(const int64_t& sequence, const Sequence& cursor, const std::vector<Sequence*>& dependents,
                           const std::atomic<bool>& alerted, const Waiter& locker) {
        int64_t availableSequence = InitialCursorValue;

        /**
         * BlockingStrategy is a special case where the unblock signal comes from the sequencer.
         * This is why we need to wait on the cursor first, and then on the dependents.
         */
        if ((availableSequence = cursor.sequence()) < sequence) {
            std::unique_lock<std::recursive_mutex> ulock(mtx);
            while ((availableSequence = cursor.sequence()) < sequence) {
                if (alerted) return AlertedSignal;

                // locker indicate if a timeout occurred
                if (locker(ulock)) return TimeoutSignal;
            }
        }

        // Now we wait on dependents.
        if (dependents.size()) {
            while ((availableSequence = GetMinimumSequence(dependents)) < sequence) {
                if (alerted) return AlertedSignal;
            }
        }
        return availableSequence;
    }

private:
    std::recursive_mutex mtx;
    std::condition_variable_any consumerNotifyCondition;

    DISALLOW_COPY_MOVE_AND_ASSIGN(BlockingStrategy);
};

static inline std::function<int64_t()> buildMinSequenceFunction(const Sequence& cursor,
                                                                const std::vector<Sequence*>& dependents) {
    if (!dependents.size())
        return [&cursor]() { return cursor.sequence(); };
    else
        return [&dependents]() { return GetMinimumSequence(dependents); };
}
}  // namespace disruptor

#endif
