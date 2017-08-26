#include "catch.hpp"
#include "pattern/disruptor/SequenceBarrier.h"

using namespace disruptor;

TEST_CASE("BasicSetterAndGetter", "[SequenceBarrier]") {
    Sequence cursor;
    std::vector<Sequence*> dependents;
    SequenceBarrier<> barrier(cursor, dependents);

    REQUIRE(!barrier.get_alerted());
    barrier.set_alerted(true);
    REQUIRE(barrier.get_alerted());
}

TEST_CASE("SequenceBarrier WaitForCursor", "[SequenceBarrier]") {
    Sequence cursor;
    std::vector<Sequence*> dependents;
    SequenceBarrier<> barrier(cursor, dependents);

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() { returnValue.store(barrier.WaitFor(FirstSequenceValue)); });

    REQUIRE(returnValue.load() == InitialCursorValue);
    std::thread([&]() { cursor.IncrementAndGet(1L); }).join();
    waiter.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);

    std::thread waiter2(
        [&]() { returnValue.store(barrier.WaitFor(FirstSequenceValue + 1L, std::chrono::seconds(5))); });

    std::thread([&]() { cursor.IncrementAndGet(1L); }).join();

    waiter2.join();
    REQUIRE(returnValue.load() == FirstSequenceValue + 1L);
}
