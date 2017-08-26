#include "catch.hpp"
#include "pattern/disruptor/ClaimStrategy.h"

using namespace disruptor;

static std::vector<Sequence*> one_dependents(Sequence& seq1) {
    std::vector<Sequence*> d = {&seq1};
    return d;
}

static const int RING_BUFFER_SIZE = 8;

TEST_CASE("IncrementAndGet", "[SingleThreadedStrategy]") {
    std::vector<Sequence*> emptyDependents;
    SingleThreadedStrategy<RING_BUFFER_SIZE> strategy;

    int64_t nextSeq = strategy.IncrementAndGet(emptyDependents);
    REQUIRE(nextSeq == FirstSequenceValue);

    const size_t delta = 10;
    nextSeq = strategy.IncrementAndGet(emptyDependents, delta);
    REQUIRE(nextSeq == FirstSequenceValue + delta);
}

TEST_CASE("HasAvailableCapacity", "[SingleThreadedStrategy]") {
    Sequence seq1;
    SingleThreadedStrategy<RING_BUFFER_SIZE> strategy;

    auto oneDependents = one_dependents(seq1);

    int64_t nextSeq = strategy.IncrementAndGet(oneDependents, RING_BUFFER_SIZE);
    REQUIRE(nextSeq == InitialCursorValue + RING_BUFFER_SIZE);
    REQUIRE(!strategy.HasAvailableCapacity(oneDependents));

    // advance late consumers
    seq1.IncrementAndGet(1L);
    REQUIRE(strategy.HasAvailableCapacity(oneDependents));

    // only one slot free
    REQUIRE(strategy.IncrementAndGet(oneDependents) == nextSeq + 1L);

    // dependent keeps up
    seq1.IncrementAndGet(RING_BUFFER_SIZE);

    // all equals
    REQUIRE(strategy.IncrementAndGet(oneDependents, RING_BUFFER_SIZE) == seq1.IncrementAndGet(RING_BUFFER_SIZE));
}

TEST_CASE("SingleIncrementAndGet", "[MultiThreadedStrategy]") {
    std::vector<Sequence*> emptyDependents;
    MultiThreadedStrategy<RING_BUFFER_SIZE> strategy;

    std::atomic<int64_t> nextSeq(InitialCursorValue);
    std::thread([&]() { nextSeq.store(strategy.IncrementAndGet(emptyDependents)); }).join();
    REQUIRE(nextSeq == FirstSequenceValue);
}

TEST_CASE("DualIncrementAndGet", "[MultiThreadedStrategy]") {
    std::vector<Sequence*> emptyDependents;
    MultiThreadedStrategy<RING_BUFFER_SIZE> strategy;

    std::atomic<int64_t> nextSeq1, nextSeq2 = {InitialCursorValue};
    std::atomic<bool> wait1, wait2 = {true};

    std::thread publisher1([&]() {
        while (wait1)
            ;
        nextSeq1 = strategy.IncrementAndGet(emptyDependents);
    });

    std::thread publisher2([&]() {
        while (wait2)
            ;
        nextSeq2 = strategy.IncrementAndGet(emptyDependents);
    });

    wait1 = false;
    publisher1.join();

    wait2 = false;
    publisher2.join();

    REQUIRE(nextSeq1 == FirstSequenceValue);
    REQUIRE(nextSeq2 == FirstSequenceValue + 1L);
}

TEST_CASE("MultiThreadedStrategy", "[HasAvailableCapacity]") {
    Sequence seq1;
    MultiThreadedStrategy<RING_BUFFER_SIZE> strategy;

    auto oneDependents = one_dependents(seq1);

    int64_t nextSeq = strategy.IncrementAndGet(oneDependents, RING_BUFFER_SIZE);
    REQUIRE(nextSeq == InitialCursorValue + RING_BUFFER_SIZE);
    REQUIRE(!strategy.HasAvailableCapacity(oneDependents));

    // advance late consumers
    seq1.IncrementAndGet(1L);
    REQUIRE(strategy.HasAvailableCapacity(oneDependents));

    // only one slot free
    REQUIRE(strategy.IncrementAndGet(oneDependents) == nextSeq + 1L);

    // dependent keeps up
    seq1.IncrementAndGet(RING_BUFFER_SIZE);

    // all equals
    REQUIRE(strategy.IncrementAndGet(oneDependents, RING_BUFFER_SIZE) == seq1.IncrementAndGet(RING_BUFFER_SIZE));
}

TEST_CASE("SynchronizePublishingShouldBlockEagerThreads", "[MultiThreadedStrategy]") {
    std::vector<Sequence*> emptyDependents;
    MultiThreadedStrategy<RING_BUFFER_SIZE> strategy;
    std::atomic<bool> running1(true), running2(true), running3(true);
    std::atomic<bool> wait1(true), wait2(true), wait3(true);
    Sequence claimed1, claimed2, claimed3;
    Sequence cursor;

    std::thread publisher1([&]() {
        while (wait1)
            ;
        claimed1.set_sequence(strategy.IncrementAndGet(emptyDependents));
        wait1 = true;
        while (wait1)
            ;
        strategy.SynchronizePublishing(FirstSequenceValue, cursor, 1);
        running1 = false;
    });

    std::thread publisher2([&]() {
        while (wait2)
            ;
        claimed2.set_sequence(strategy.IncrementAndGet(emptyDependents));
        wait2 = true;
        while (wait2)
            ;
        strategy.SynchronizePublishing(FirstSequenceValue + 1, cursor, 1);
        running2 = false;
    });

    std::thread publisher3([&]() {
        while (wait3)
            ;
        claimed3.set_sequence(strategy.IncrementAndGet(emptyDependents));
        wait3 = true;
        while (wait3)
            ;
        strategy.SynchronizePublishing(FirstSequenceValue + 2, cursor, 1);
        running3 = false;
    });

    // publisher1 claims
    wait1 = false;
    while (!wait1)
        ;
    REQUIRE(claimed1.sequence() == FirstSequenceValue);
    REQUIRE(claimed2.sequence() == InitialCursorValue);
    REQUIRE(claimed3.sequence() == InitialCursorValue);

    // publisher2 claims
    wait2 = false;
    while (!wait2)
        ;
    REQUIRE(claimed1.sequence() == FirstSequenceValue);
    REQUIRE(claimed2.sequence() == FirstSequenceValue + 1);
    REQUIRE(claimed3.sequence() == InitialCursorValue);

    // publisher3 claims
    wait3 = false;
    while (!wait3)
        ;
    REQUIRE(claimed1.sequence() == FirstSequenceValue);
    REQUIRE(claimed2.sequence() == FirstSequenceValue + 1);
    REQUIRE(claimed3.sequence() == FirstSequenceValue + 2);

    // publisher 2 and 3 continue running but must wait on publisher 3 to publish
    wait3 = false;
    wait2 = false;
    REQUIRE(running2);
    REQUIRE(running3);

    // publisher1 publish his sequence
    wait1 = false;
    publisher1.join();
    REQUIRE(running2);
    REQUIRE(running3);

    // sequencer commit the cursor
    cursor.IncrementAndGet(1);

    // publisher2 is now free to run
    publisher2.join();
    // publisher3 is still locked
    REQUIRE(running3);

    // sequencer commit the cursor once more
    cursor.IncrementAndGet(1);
    publisher3.join();
}
