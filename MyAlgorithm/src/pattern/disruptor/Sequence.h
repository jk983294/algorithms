#ifndef CACHE_LINE_SIZE_IN_BYTES
#define CACHE_LINE_SIZE_IN_BYTES 64
#endif

#define ATOMIC_SEQUENCE_PADDING_LENGTH (CACHE_LINE_SIZE_IN_BYTES - sizeof(std::atomic<int64_t>)) / 8
#define SEQUENCE_PADDING_LENGTH (CACHE_LINE_SIZE_IN_BYTES - sizeof(int64_t)) / 8

#ifndef DISRUPTOR_SEQUENCE_H_
#define DISRUPTOR_SEQUENCE_H_

#include <atomic>
#include <climits>
#include "utils.h"

namespace disruptor {

// special cursor values
constexpr int64_t InitialCursorValue = -1L;
constexpr int64_t AlertedSignal = -2L;
constexpr int64_t TimeoutSignal = -3L;
constexpr int64_t FirstSequenceValue = InitialCursorValue + 1L;

class Sequence {
public:
    /**
     * construct a sequence counter that can be tracked across threads.
     */
    Sequence(int64_t initial_value = InitialCursorValue) : sequence_(initial_value) {}

    /**
     * get the current value of the Sequence
     */
    int64_t sequence() const { return sequence_.load(std::memory_order::memory_order_acquire); }

    /**
     * set the current value of the Sequence
     */
    void set_sequence(int64_t value) { sequence_.store(value, std::memory_order::memory_order_release); }

    /**
     * increment and return the changed value of the Sequence
     */
    int64_t IncrementAndGet(const int64_t& increment) {
        return sequence_.fetch_add(increment, std::memory_order::memory_order_release) + increment;
    }

private:
    int64_t padding0_[ATOMIC_SEQUENCE_PADDING_LENGTH];  // padding
    std::atomic<int64_t> sequence_;
    int64_t padding1_[ATOMIC_SEQUENCE_PADDING_LENGTH];  // padding

    DISALLOW_COPY_MOVE_AND_ASSIGN(Sequence);
};

inline int64_t GetMinimumSequence(const std::vector<Sequence*>& sequences) {
    int64_t minimum = LONG_MAX;
    for (Sequence* sequence_ : sequences) {
        const int64_t sequence = sequence_->sequence();
        minimum = minimum < sequence ? minimum : sequence;
    }
    return minimum;
}
}

#endif
