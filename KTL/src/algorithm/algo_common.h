#ifndef _ALGORITHM_COMMON_H_
#define _ALGORITHM_COMMON_H_

#include <cassert>
#include <cstring>
#include "../iterator/iterator.h"
#include "../iterator/typetraits.h"

/**
include distance, advance
*/
namespace ktl {

//********** [distance] ******************************
template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type _distance(InputIterator first, InputIterator last,
                                                                   input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type dist = 0;
    while (first++ != last) {
        ++dist;
    }
    return dist;
}

template <class RandomIterator>
typename iterator_traits<RandomIterator>::difference_type _distance(RandomIterator first, RandomIterator last,
                                                                    random_access_iterator_tag) {
    auto dist = last - first;
    return dist;
}

template <class Iterator>
typename iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last) {
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    return _distance(first, last, iterator_category());
}

//********** [advance] ******************************
template <class InputIterator, class Distance>
void _advance(InputIterator &it, Distance n, input_iterator_tag) {
    assert(n >= 0);
    while (n--) {
        ++it;
    }
}
template <class BidirectionIterator, class Distance>
void _advance(BidirectionIterator &it, Distance n, bidirectional_iterator_tag) {
    if (n < 0) {
        while (n++) {
            --it;
        }
    } else {
        while (n--) {
            ++it;
        }
    }
}
template <class RandomIterator, class Distance>
void _advance(RandomIterator &it, Distance n, random_access_iterator_tag) {
    if (n < 0) {
        it -= (-n);
    } else {
        it += n;
    }
}

template <class InputIterator, class Distance>
void advance(InputIterator &it, Distance n) {
    typedef typename iterator_traits<InputIterator>::iterator_category iterator_category;
    _advance(it, n, iterator_category());
}

template <class T>
void swap(T &x, T &y) {
    T tmp = x;
    x = y;
    y = tmp;
}
}

#endif
