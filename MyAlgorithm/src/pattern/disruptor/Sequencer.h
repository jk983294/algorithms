#ifndef DISRUPTOR_SEQUENCER_H_
#define DISRUPTOR_SEQUENCER_H_

#include "ClaimStrategy.h"
#include "SequenceBarrier.h"
#include "WaitStrategy.h"

namespace disruptor {

/**
 * Coordinator for claiming sequences for access to a data structures while tracking dependent Sequences
 * @tparam T
 * @tparam N RingBufferSize
 * @tparam C ClaimStrategy
 * @tparam W WaitStrategy
 */
template <typename T, size_t N = DefaultRingBufferSize, typename C = DefaultClaimStrategy,
          typename W = DefaultWaitStrategy>
class Sequencer {
public:
    /**
     * construct a Sequencer with the selected strategies
     * @param events
     */
    Sequencer(std::array<T, N> events) : ringBuffer(events) {}

    /**
     * Set the sequences that will gate publishers to prevent the buffer wrapping
     * @param sequences sequences to be gated on
     */
    void set_gating_sequences(const std::vector<Sequence*>& sequences) { gatingSequences = sequences; }

    /**
     * create a SequenceBarrier that gates on the cursor and a list of Sequences
     * @param dependents this barrier will track
     * @return the barrier gated as required
     */
    SequenceBarrier<W> NewBarrier(const std::vector<Sequence*>& dependents) {
        return SequenceBarrier<W>(cursor, dependents);
    }

    /**
     * get the value of the cursor indicating the published sequence
     * @return value of the cursor for events that have been published
     */
    int64_t GetCursor() { return cursor.sequence(); }

    /**
     * Has the buffer capacity left to allocate another sequence.
     * This is a concurrent method so the response should only be taken as an indication of available capacity
     * @return true if the buffer has the capacity to allocated another event
     */
    bool HasAvailableCapacity() { return claimStrategy.HasAvailableCapacity(gatingSequences); }

    /**
     * claim the next batch of sequence numbers for publishing
     * @param delta the requested number of sequences
     * @return the maximal claimed sequence
     */
    int64_t Claim(size_t delta = 1) { return claimStrategy.IncrementAndGet(gatingSequences, delta); }

    /**
     * publish an event and make it visible to EventProcessor
     * @param sequence sequence to be published
     * @param delta
     */
    void Publish(const int64_t& sequence, size_t delta = 1) {
        claimStrategy.SynchronizePublishing(sequence, cursor, delta);
        const int64_t new_cursor = cursor.IncrementAndGet(delta);
        waitStrategy.SignalAllWhenBlocking();
    }

    T& operator[](const int64_t& sequence) { return ringBuffer[sequence]; }

private:
    RingBuffer<T, N> ringBuffer;

    Sequence cursor;

    C claimStrategy;

    W waitStrategy;

    std::vector<Sequence*> gatingSequences;

    DISALLOW_COPY_MOVE_AND_ASSIGN(Sequencer);
};
}

#endif
