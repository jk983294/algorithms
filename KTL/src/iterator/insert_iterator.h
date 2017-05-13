#ifndef _INSERT_ITERATOR_H
#define _INSERT_ITERATOR_H

#include "iterator.h"

namespace ktl {

template <class Container>
class back_insert_iterator {
protected:
    Container* container;

public:
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    explicit back_insert_iterator(Container& x) : container(&x) {}
    back_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
        container->push_back(value);
        return *this;
    }

    // close below functionality
    back_insert_iterator<Container>& operator*() { return *this; };
    back_insert_iterator<Container>& operator++() { return *this; };
    back_insert_iterator<Container>& operator++(int) { return *this; };
};

template <class Container>
class front_insert_iterator {
protected:
    Container* container;

public:
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    explicit front_insert_iterator(Container& x) : container(&x) {}
    front_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
        container->push_front(value);
        return *this;
    }

    // close below functionality
    front_insert_iterator<Container>& operator*() { return *this; };
    front_insert_iterator<Container>& operator++() { return *this; };
    front_insert_iterator<Container>& operator++(int) { return *this; };
};

template <class Container>
class insert_iterator {
protected:
    Container* container;
    typename Container::iterator iter;

public:
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    explicit insert_iterator(Container& x, typename Container::iterator i) : container(&x), iter(i) {}
    insert_iterator<Container>& operator=(const typename Container::value_type& value) {
        iter = container->insert(iter, value);
        ++iter;  // update internal iterator to next insert position
        return *this;
    }

    // close below functionality
    insert_iterator<Container>& operator*() { return *this; };
    insert_iterator<Container>& operator++() { return *this; };
    insert_iterator<Container>& operator++(int) { return *this; };
};

template <class Container>
inline back_insert_iterator<Container> back_inserter(Container& x) {
    return back_insert_iterator<Container>(x);
}
template <class Container>
inline front_insert_iterator<Container> front_inserter(Container& x) {
    return front_insert_iterator<Container>(x);
}
template <class Container, class Iterator>
inline insert_iterator<Container> inserter(Container& x, Iterator i) {
    return insert_iterator<Container>(x, iter(i));
}
}
#endif
