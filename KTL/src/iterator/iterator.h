#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <cstddef>

namespace ktl {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class T, class Distance>
struct input_iterator {  // read only
    typedef input_iterator_tag iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef T* pointer;
    typedef T& reference;
};

template <class T, class Distance>
struct output_iterator {  // write only
    typedef output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;
};

template <class T, class Distance>
struct forward_iterator {
    typedef forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef T* pointer;
    typedef T& reference;
};

template <class T, class Distance>
struct bidirectional_iterator {
    typedef bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef T* pointer;
    typedef T& reference;
};
template <class T, class Distance>
struct random_access_iterator {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef T* pointer;
    typedef T& reference;
};

// all iterator should inherit from this ktl::iterator
template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

template <class Iterator>
struct iterator_traits {
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
};

// partial specialization for T*, raw pointer is a random_access_iterator
template <class T>
struct iterator_traits<T*> {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};

// partial specialization for const T*, raw pointer is a random_access_iterator
template <class T>
struct iterator_traits<const T*> {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T* pointer;
    typedef const T& reference;
};

template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator& It) {
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}

// not easy to give T(), but easy to give T*, just cast nullptr of T*
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator& It) {
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

// not easy to give T(), but easy to give T*, just cast nullptr of T*
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type* difference_type(const Iterator& It) {
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}
}

#endif
