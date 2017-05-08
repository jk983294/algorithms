#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_

#include "../algorithm/algorithm.h"
#include "construct.h"

namespace ktl {

// copy for POD
template <class InputIterator, class ForwardIterator>
ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _true_type) {
    memcpy(result, first, (last - first) * sizeof(*first));
    return result + (last - first);
}

// copy for non-POD
template <class InputIterator, class ForwardIterator>
ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type) {
    for (; first != last; ++first, ++result) {
        construct(result, *first);
    }
    return result;
}

template <class InputIterator, class ForwardIterator, class T>
ForwardIterator _uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*) {
    typedef typename _type_traits<T>::is_POD_type isPOD;
    return _uninitialized_copy_aux(first, last, result, isPOD());
}

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
    return _uninitialized_copy(first, last, result, value_type(result));
}

template <class ForwardIterator, class T>
void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type) {
    fill(first, last, value);
}

template <class ForwardIterator, class T>
void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type) {
    for (; first != last; ++first) {
        construct(first, value);  // non POD
    }
}

template <class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value) {
    typedef typename _type_traits<T>::is_POD_type isPOD;
    _uninitialized_fill_aux(first, last, value, isPOD());
}

template <class ForwardIterator, class Size, class T>
ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _true_type) {
    return fill_n(first, n, x);
}

template <class ForwardIterator, class Size, class T>
ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _false_type) {
    int i = 0;
    for (; i != n; ++i, ++first) {
        construct((T*)(first), x);  // non POD
    }
    return first;
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
    typedef typename _type_traits<T>::is_POD_type isPOD;
    return _uninitialized_fill_n_aux(first, n, x, isPOD());
}
}
#endif
