#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "../sequence/deque.h"

namespace ktl {

template <class T, class Sequence = deque<T> >
class queue {
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef const reference const_reference;

protected:
    Sequence c;  // underline container
public:
    queue() {}
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    void clear() { c.clear(); }

    const_reference front() { return c.front(); }
    const_reference back() { return c.back(); }

    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_front(); }
};
}

#endif
