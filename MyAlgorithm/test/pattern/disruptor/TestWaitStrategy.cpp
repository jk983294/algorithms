#include "catch.hpp"
#include "pattern/disruptor/WaitStrategy.h"

using namespace disruptor;

static std::vector<Sequence*> all_dependents(Sequence& seq1, Sequence& seq2, Sequence& seq3) {
    std::vector<Sequence*> d = {&seq1, &seq2, &seq3};
    return d;
}

TEST_CASE("WaitForCursor", "[BusySpinStrategy]") {
    std::atomic<int64_t> returnValue(InitialCursorValue);
    Sequence cursor;
    std::vector<Sequence*> dependents;
    BusySpinStrategy strategy;
    std::atomic<bool> alerted;

    std::thread waiter([&]() { returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted)); });

    REQUIRE(returnValue.load() == InitialCursorValue);
    std::thread([&]() {
        cursor.IncrementAndGet(1L);
        strategy.SignalAllWhenBlocking();
    }).join();
    waiter.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("Signal Timeout Waiting On Cursor", "[BusySpinStrategy]") {
    Sequence cursor;
    std::vector<Sequence*> dependents;
    BusySpinStrategy strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(
            strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted, std::chrono::microseconds(1L)));
    });

    waiter.join();
    REQUIRE(returnValue.load() == TimeoutSignal);

    std::thread waiter2([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted, std::chrono::seconds(1L)));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    waiter2.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("WaitForDependents", "[BusySpinStrategy]") {
    Sequence cursor;
    Sequence seq1;
    Sequence seq2;
    Sequence seq3;
    std::vector<Sequence*> dependents;
    BusySpinStrategy strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, all_dependents(seq1, seq2, seq3), alerted));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    // dependents haven't moved, WaitFor() should still block.
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq1.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq2.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq3.IncrementAndGet(1L);
    waiter.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("SignalAlertWaitingOnDependents", "[BusySpinStrategy]") {
    Sequence cursor;
    Sequence seq1;
    Sequence seq2;
    Sequence seq3;
    std::vector<Sequence*> dependents;
    BusySpinStrategy strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, all_dependents(seq1, seq2, seq3), alerted));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    // dependents haven't moved, WaitFor() should still block.
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq1.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq2.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    alerted.store(true);

    waiter.join();
    REQUIRE(returnValue.load() == AlertedSignal);
}

TEST_CASE("YieldingStrategy WaitForCursor", "[YieldingStrategy]") {
    std::atomic<int64_t> returnValue(InitialCursorValue);
    Sequence cursor;
    std::vector<Sequence*> dependents;
    YieldingStrategy<> strategy;
    std::atomic<bool> alerted;

    std::thread waiter([&]() { returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted)); });

    REQUIRE(returnValue.load() == InitialCursorValue);
    std::thread([&]() {
        cursor.IncrementAndGet(1L);
        strategy.SignalAllWhenBlocking();
    }).join();
    waiter.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("YieldingStrategy Signal Timeout Waiting On Cursor", "[YieldingStrategy]") {
    Sequence cursor;
    std::vector<Sequence*> dependents;
    YieldingStrategy<> strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(
            strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted, std::chrono::microseconds(1L)));
    });

    waiter.join();
    REQUIRE(returnValue.load() == TimeoutSignal);

    std::thread waiter2([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted, std::chrono::seconds(1L)));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    waiter2.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("YieldingStrategy WaitForDependents", "[YieldingStrategy]") {
    Sequence cursor;
    Sequence seq1;
    Sequence seq2;
    Sequence seq3;
    std::vector<Sequence*> dependents;
    YieldingStrategy<> strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, all_dependents(seq1, seq2, seq3), alerted));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    // dependents haven't moved, WaitFor() should still block.
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq1.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq2.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq3.IncrementAndGet(1L);
    waiter.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("YieldingStrategy SignalAlertWaitingOnDependents", "[YieldingStrategy]") {
    Sequence cursor;
    Sequence seq1;
    Sequence seq2;
    Sequence seq3;
    std::vector<Sequence*> dependents;
    YieldingStrategy<> strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, all_dependents(seq1, seq2, seq3), alerted));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    // dependents haven't moved, WaitFor() should still block.
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq1.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq2.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    alerted.store(true);

    waiter.join();
    REQUIRE(returnValue.load() == AlertedSignal);
}

TEST_CASE("SleepingStrategy WaitForCursor", "[SleepingStrategy]") {
    std::atomic<int64_t> returnValue(InitialCursorValue);
    Sequence cursor;
    std::vector<Sequence*> dependents;
    SleepingStrategy<> strategy;
    std::atomic<bool> alerted;

    std::thread waiter([&]() { returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted)); });

    REQUIRE(returnValue.load() == InitialCursorValue);
    std::thread([&]() {
        cursor.IncrementAndGet(1L);
        strategy.SignalAllWhenBlocking();
    }).join();
    waiter.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("SleepingStrategy Signal Timeout Waiting On Cursor", "[SleepingStrategy]") {
    Sequence cursor;
    std::vector<Sequence*> dependents;
    SleepingStrategy<> strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(
            strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted, std::chrono::microseconds(1L)));
    });

    waiter.join();
    REQUIRE(returnValue.load() == TimeoutSignal);

    std::thread waiter2([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted, std::chrono::seconds(1L)));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    waiter2.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("SleepingStrategy WaitForDependents", "[SleepingStrategy]") {
    Sequence cursor;
    Sequence seq1;
    Sequence seq2;
    Sequence seq3;
    std::vector<Sequence*> dependents;
    SleepingStrategy<> strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, all_dependents(seq1, seq2, seq3), alerted));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    // dependents haven't moved, WaitFor() should still block.
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq1.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq2.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq3.IncrementAndGet(1L);
    waiter.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("SleepingStrategy SignalAlertWaitingOnDependents", "[SleepingStrategy]") {
    Sequence cursor;
    Sequence seq1;
    Sequence seq2;
    Sequence seq3;
    std::vector<Sequence*> dependents;
    SleepingStrategy<> strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, all_dependents(seq1, seq2, seq3), alerted));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    // dependents haven't moved, WaitFor() should still block.
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq1.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq2.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    alerted.store(true);

    waiter.join();
    REQUIRE(returnValue.load() == AlertedSignal);
}

TEST_CASE("BlockingStrategy WaitForCursor", "[BlockingStrategy]") {
    std::atomic<int64_t> returnValue(InitialCursorValue);
    Sequence cursor;
    std::vector<Sequence*> dependents;
    BlockingStrategy strategy;
    std::atomic<bool> alerted;

    std::thread waiter([&]() { returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted)); });

    REQUIRE(returnValue.load() == InitialCursorValue);
    std::thread([&]() {
        cursor.IncrementAndGet(1L);
        strategy.SignalAllWhenBlocking();
    }).join();
    waiter.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("BlockingStrategy Signal Timeout Waiting On Cursor", "[BlockingStrategy]") {
    Sequence cursor;
    std::vector<Sequence*> dependents;
    BlockingStrategy strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(
            strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted, std::chrono::microseconds(1L)));
    });

    waiter.join();
    REQUIRE(returnValue.load() == TimeoutSignal);

    std::thread waiter2([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, dependents, alerted, std::chrono::seconds(1L)));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    waiter2.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("BlockingStrategy WaitForDependents", "[BlockingStrategy]") {
    Sequence cursor;
    Sequence seq1;
    Sequence seq2;
    Sequence seq3;
    std::vector<Sequence*> dependents;
    BlockingStrategy strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, all_dependents(seq1, seq2, seq3), alerted));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    // dependents haven't moved, WaitFor() should still block.
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq1.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq2.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq3.IncrementAndGet(1L);
    waiter.join();
    REQUIRE(returnValue.load() == FirstSequenceValue);
}

TEST_CASE("BlockingStrategy SignalAlertWaitingOnDependents", "[BlockingStrategy]") {
    Sequence cursor;
    Sequence seq1;
    Sequence seq2;
    Sequence seq3;
    std::vector<Sequence*> dependents;
    BlockingStrategy strategy;
    std::atomic<bool> alerted;

    std::atomic<int64_t> returnValue(InitialCursorValue);

    std::thread waiter([&]() {
        returnValue.store(strategy.WaitFor(FirstSequenceValue, cursor, all_dependents(seq1, seq2, seq3), alerted));
    });

    cursor.IncrementAndGet(1L);
    strategy.SignalAllWhenBlocking();
    // dependents haven't moved, WaitFor() should still block.
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq1.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    seq2.IncrementAndGet(1L);
    REQUIRE(returnValue.load() == InitialCursorValue);

    alerted.store(true);

    waiter.join();
    REQUIRE(returnValue.load() == AlertedSignal);
}
