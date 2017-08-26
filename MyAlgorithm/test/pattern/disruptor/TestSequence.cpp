#include "catch.hpp"
#include "pattern/disruptor/Sequence.h"

using namespace disruptor;

TEST_CASE("Sequence", "[Sequence]") {
    Sequence seq;

    REQUIRE(seq.sequence() == InitialCursorValue);

    seq.set_sequence(2L);
    REQUIRE(seq.sequence() == 2L);

    REQUIRE(seq.IncrementAndGet(1L) == 3L);
    REQUIRE(seq.IncrementAndGet(2L) == 5L);

    // AtLeastOneCacheLine
    REQUIRE(sizeof(Sequence) >= CACHE_LINE_SIZE_IN_BYTES);

    // IsCacheLineAligned
    REQUIRE(alignof(Sequence) == CACHE_LINE_SIZE_IN_BYTES / 8);
}
