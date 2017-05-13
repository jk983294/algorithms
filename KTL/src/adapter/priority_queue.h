#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

#include "../sequence/vector.h"

namespace ktl {

template <class T, class Sequence = vector<T> >
class priority_queue {
public:
    typedef typename Sequence::value_type value_type;
    typedef typename Sequence::size_type size_type;
    typedef typename Sequence::reference reference;
    typedef const reference const_reference;

protected:
    Sequence c;  // underline container
public:
    priority_queue() : c() {}

    template <class InputIterator>
    priority_queue(InputIterator first, InputIterator last) : c(first, last) {
        make_heap(c.begin(), c.end());
    }

    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    void clear() { c.clear(); }

    const_reference top() { return c.front(); }
    void push(const value_type& x) {
        c.push_back(x);
        push_heap(c.begin(), c.end());
    }
    void pop() {
        pop_heap(c.begin(), c.end());
        c.pop_back();
    }
};
}

#endif
