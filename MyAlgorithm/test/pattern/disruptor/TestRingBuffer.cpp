#include "catch.hpp"
#include "pattern/disruptor/RingBuffer.h"

using namespace disruptor;

int f(const int i) { return i + 1; }

TEST_CASE("RingBuffer", "[RingBuffer]") {
    const int RING_BUFFER_SIZE = 8;

    std::array<int, RING_BUFFER_SIZE> tmp;
    for (int i = 0; i < RING_BUFFER_SIZE; i++) tmp[i] = f(i);

    RingBuffer<int, RING_BUFFER_SIZE> ringBuffer(tmp);

    for (size_t i = 0; i < RING_BUFFER_SIZE * 2; i++) REQUIRE(ringBuffer[i] == f(i % RING_BUFFER_SIZE));

    for (size_t i = 0; i < RING_BUFFER_SIZE * 2; i++) const auto& t = ringBuffer[i];
}
