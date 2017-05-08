#ifndef _ALGORITHM_HEAP_H_
#define _ALGORITHM_HEAP_H_

#include <cassert>
#include <cstring>
#include "../iterator/iterator.h"
#include "../iterator/typetraits.h"
#include "algo_common.h"

namespace ktl {

template <class RandomAccessIterator, class Distance, class T>
inline void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value) {
    Distance parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && *(first + parent) < value) {
        *(first + holeIndex) = *(first + parent);  // move parent down
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;  // until find the hole fit inserted value
}

template <class RandomAccessIterator, class Distance, class T>
inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance *, T *) {
    __push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
}

template <class RandomAccessIterator>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
    // new element already at tail of container
    __push_heap_aux(first, last, difference_type(first), value_type(first));
}

template <class RandomAccessIterator, class T, class Distance>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value) {
    Distance topIndex = holeIndex;
    Distance targetChild = 2 * (holeIndex + 1);
    while (targetChild < len) {
        if (*(first + targetChild) < *(first + (targetChild - 1))) targetChild--;
        // move targetChild up to hole position
        *(first + holeIndex) = *(first + targetChild);
        holeIndex = targetChild;
        targetChild = 2 * (targetChild + 1);
    }
    if (targetChild == len) {  // no right child, only left
        *(first + holeIndex) = *(first + (targetChild - 1));
        holeIndex = targetChild - 1;
    }
    __push_heap(first, holeIndex, topIndex, value);
}

template <class RandomAccessIterator, class T, class Distance>
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value,
                       Distance *) {
    *result = *first;  // save root to tail of container
    // adjust value to proper position, value is orignal tail
    __adjust_heap(first, Distance(0), Distance(last - first), value);
}

template <class RandomAccessIterator, class T>
inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T *) {
    __pop_heap(first, last - 1, last - 1, T(*(last - 1)), difference_type(first));
}

template <class RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
    __pop_heap_aux(first, last, value_type(first));
}

template <class RandomIterator, class T, class Distance>
void __make_heap(RandomIterator first, RandomIterator last, T *, Distance *) {
    if (last - first < 2) return;
    Distance len = last - first;
    Distance parent = (len - 2) / 2;
    while (true) {
        __adjust_heap(first, parent, len, T(*(first + parent)));
        if (parent == 0) return;
        parent--;
    }
}

template <class RandomIterator>
inline void make_heap(RandomIterator first, RandomIterator last) {
    __make_heap(first, last, value_type(first), difference_type(first));
}

template <class RandomAccessIterator>
void heap_sort(RandomAccessIterator first, RandomAccessIterator last) {
    while (last - first > 1) pop_heap(first, last--);
}
}

#endif
