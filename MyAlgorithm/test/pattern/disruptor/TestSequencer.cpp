#include "catch.hpp"
#include "pattern/disruptor/Sequencer.h"

using namespace disruptor;

TEST_CASE("Sequencer", "[Sequencer]") {
    const int RING_BUFFER_SIZE = 4;
    std::array<long, RING_BUFFER_SIZE> events{1L, 2L, 3L, 4L};
    Sequencer<long, RING_BUFFER_SIZE, SingleThreadedStrategy<RING_BUFFER_SIZE>, DefaultWaitStrategy> sequencer(events);

    REQUIRE(sequencer.GetCursor() == InitialCursorValue);
}
