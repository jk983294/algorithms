#ifndef DISRUPTOR_RING_BUFFER_H_
#define DISRUPTOR_RING_BUFFER_H_

#include <array>
#include "utils.h"

namespace disruptor {

constexpr size_t DefaultRingBufferSize = 1024;

template <typename T, size_t N = DefaultRingBufferSize>
class RingBuffer {
public:
    RingBuffer(const std::array<T, N>& events) : events_(events) {}

    static_assert(((N > 0) && ((N & (~N + 1)) == N)), "RingBuffer's size must be a positive power of 2");

    /**
     * get the event for a given sequence in the RingBuffer.
     * @param sequence
     * @return event reference at the specified sequence position
     */
    T& operator[](const int64_t& sequence) { return events_[sequence & (N - 1)]; }

    const T& operator[](const int64_t& sequence) const { return events_[sequence & (N - 1)]; }

private:
    std::array<T, N> events_;

    DISALLOW_COPY_MOVE_AND_ASSIGN(RingBuffer);
};
}

#endif
