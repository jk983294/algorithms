#ifndef DISRUPTOR_SEQUENCE_BARRIER_H_  // NOLINT
#define DISRUPTOR_SEQUENCE_BARRIER_H_  // NOLINT

#include <memory>
#include <vector>

#include "Sequence.h"
#include "WaitStrategy.h"

namespace disruptor {

template <typename W = DefaultWaitStrategy>
class SequenceBarrier {
public:
    SequenceBarrier(const Sequence& c, const std::vector<Sequence*>& d) : cursor(c), dependents(d), alerted(false) {}

    int64_t WaitFor(const int64_t& seq) { return waitStrategy.WaitFor(seq, cursor, dependents, alerted); }

    template <class R, class P>
    int64_t WaitFor(const int64_t& seq, const std::chrono::duration<R, P>& timeout) {
        return waitStrategy.WaitFor(seq, cursor, dependents, alerted, timeout);
    }

    int64_t get_sequence() const { return cursor.sequence(); }

    bool get_alerted() const { return alerted.load(std::memory_order::memory_order_acquire); }

    void set_alerted(bool alert) { alerted.store(alert, std::memory_order::memory_order_release); }

private:
    W waitStrategy;
    const Sequence& cursor;
    std::vector<Sequence*> dependents;
    std::atomic<bool> alerted;
};
}

#endif
