#ifndef _ALGORITHM_COPY_H_
#define _ALGORITHM_COPY_H_

#include <cassert>
#include <cstring>
#include "../iterator/insert_iterator.h"
#include "../iterator/iterator.h"
#include "../iterator/typetraits.h"
#include "algo_common.h"

namespace ktl {

//********** [copy] return last OutputIterator position ******************************
template <class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _true_type) {
    auto dist = distance(first, last);
    memcpy(result, first, sizeof(*first) * dist);  // for POD
    advance(result, dist);
    return result;
}

template <class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _false_type) {
    while (first != last) {
        *result = *first;
        ++result;
        ++first;
    }
    return result;
}

template <class InputIterator, class OutputIterator, class T>
OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result, T *) {
    typedef typename _type_traits<T>::is_POD_type is_pod;
    return __copy(first, last, result, is_pod());
}

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
    return _copy(first, last, result, value_type(first));
}

// force to use non-pod version
template <class InputIterator, class OutputIterator>
OutputIterator __copy_backward(InputIterator first, InputIterator last, OutputIterator result, _false_type f) {
    OutputIterator new_result = result - (last - first);
    return __copy(first, last, new_result, f);
}

template <class InputIterator, class OutputIterator>
OutputIterator copy_backward(InputIterator first, InputIterator last, OutputIterator result) {
    OutputIterator new_result = result - (last - first);
    return _copy(first, last, new_result, value_type(first));
}

template <>
inline char *copy(char *first, char *last, char *result) {
    auto dist = last - first;
    memcpy(result, first, sizeof(*first) * dist);
    return result + dist;
}

template <>
inline wchar_t *copy(wchar_t *first, wchar_t *last, wchar_t *result) {
    auto dist = last - first;
    memcpy(result, first, sizeof(*first) * dist);
    return result + dist;
}

// specialization for InsertIterator, InsertIterator itself manage its pointer position
template <class InputIterator, class InsertIterator>
InsertIterator __copy_inserter(InputIterator first, InputIterator last, InsertIterator result) {
    while (first != last) {
        *result = *first;
        ++first;
    }
    return result;
}
template <class InputIterator, class C>
back_insert_iterator<C> copy(InputIterator first, InputIterator last, back_insert_iterator<C> result) {
    return __copy_inserter(first, last, result);
}
template <class InputIterator, class C>
front_insert_iterator<C> copy(InputIterator first, InputIterator last, front_insert_iterator<C> result) {
    return __copy_inserter(first, last, result);
}
}

#endif
