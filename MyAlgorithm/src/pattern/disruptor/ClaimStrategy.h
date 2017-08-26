#ifndef DISRUPTOR_CLAIM_STRATEGY_H_
#define DISRUPTOR_CLAIM_STRATEGY_H_

#include <thread>
#include "RingBuffer.h"
#include "Sequence.h"

namespace disruptor {

/**
 * Strategy employed by a Publisher to wait claim and publish sequences on the sequencer
 */
template <size_t N>
class SingleThreadedStrategy;

using DefaultClaimStrategy = SingleThreadedStrategy<DefaultRingBufferSize>;

// strategy can be used when there is a single publisher thread.
template <size_t N = DefaultRingBufferSize>
class SingleThreadedStrategy {
public:
    SingleThreadedStrategy() : lastClaimedSequence(InitialCursorValue), lastConsumerSequence(InitialCursorValue) {}

    /**
     * wait for the given sequence to be available for consumption
     * @param dependents dependents sequences to wait on (mostly consumers)
     * @param delta sequences to claim
     * @return last claimed sequence
     */
    int64_t IncrementAndGet(const std::vector<Sequence*>& dependents, size_t delta = 1) {
        lastClaimedSequence += delta;
        const int64_t nextSequence = lastClaimedSequence;
        const int64_t wrapPoint = nextSequence - N;
        if (lastConsumerSequence < wrapPoint) {
            while (GetMinimumSequence(dependents) < wrapPoint) {
                std::this_thread::yield();
            }
        }
        return nextSequence;
    }

    /**
     * verify if there exists claimable sequences in a non-blocking way
     * @param dependents dependents sequences to wait on (mostly consumers)
     * @return last claimed sequence
     */
    bool HasAvailableCapacity(const std::vector<Sequence*>& dependents) {
        const int64_t wrapPoint = lastClaimedSequence + 1L - N;
        if (wrapPoint > lastConsumerSequence) {
            const int64_t min_sequence = GetMinimumSequence(dependents);
            lastConsumerSequence = min_sequence;
            if (wrapPoint > min_sequence) return false;
        }
        return true;
    }

    void SynchronizePublishing(const int64_t& sequence, const Sequence& cursor, const size_t& delta) {}

private:
    // We do not need to use atomic values since this function is called by a single publisher.
    int64_t lastClaimedSequence;
    int64_t lastConsumerSequence;

    DISALLOW_COPY_MOVE_AND_ASSIGN(SingleThreadedStrategy);
};

// strategy can be used when there are multiply publisher threads
template <size_t N = DefaultRingBufferSize>
class MultiThreadedStrategy {
public:
    MultiThreadedStrategy() {}

    /**
     * wait for the given sequence to be available for consumption
     * @param dependents dependents sequences to wait on (mostly consumers)
     * @param delta sequences to claim [default: 1]
     * @return last claimed sequence
     */
    int64_t IncrementAndGet(const std::vector<Sequence*>& dependents, size_t delta = 1) {
        const int64_t nextSequence = lastClaimedSequence.IncrementAndGet(delta);
        const int64_t wrapPoint = nextSequence - N;
        if (lastConsumerSequence.sequence() < wrapPoint) {
            while (GetMinimumSequence(dependents) < wrapPoint) {
                std::this_thread::yield();
            }
        }
        return nextSequence;
    }

    /**
     * verify if there exists claimable sequences in a non-blocking way
     * @param dependents dependents sequences to wait on (mostly consumers)
     * @return last claimed sequence
     */
    bool HasAvailableCapacity(const std::vector<Sequence*>& dependents) {
        const int64_t wrapPoint = lastClaimedSequence.sequence() + 1L - N;
        if (wrapPoint > lastConsumerSequence.sequence()) {
            const int64_t min_sequence = GetMinimumSequence(dependents);
            lastConsumerSequence.set_sequence(min_sequence);
            if (wrapPoint > min_sequence) return false;
        }
        return true;
    }

    void SynchronizePublishing(const int64_t& sequence, const Sequence& cursor, const size_t& delta) {
        int64_t myFirstSequence = sequence - delta;

        while (cursor.sequence() < myFirstSequence) {
            std::this_thread::yield();
        }
    }

private:
    Sequence lastClaimedSequence;
    Sequence lastConsumerSequence;

    DISALLOW_COPY_MOVE_AND_ASSIGN(MultiThreadedStrategy);
};
}

#endif
