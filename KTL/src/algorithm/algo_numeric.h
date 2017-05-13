#ifndef _ALGORITHM_NUMERIC_H_
#define _ALGORITHM_NUMERIC_H_

namespace ktl {

template <class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init) {
    for (; first != last; ++first) {
        init = init + *first;
    }
    return init;
}
template <class InputIterator, class T, class BinaryFunc>
T accumulate(InputIterator first, InputIterator last, T init, BinaryFunc func) {
    for (; first != last; ++first) {
        init = func(init, *first);
    }
    return init;
}

template <class InputIterator1, class InputIterator2, class T>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init) {
    for (; first1 != last1; ++first1, ++first2) init = init + (*first1 * *first2);
    return init;
}
template <class InputIterator1, class InputIterator2, class T, class BinaryFunc1, class BinaryFunc2>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, BinaryFunc1 func1,
                BinaryFunc2 func2) {
    for (; first1 != last1; ++first1, ++first2) init = func1(init, func2(*first1, *first2));
    return init;
}

template <class InputIterator, class OutputIterator, class T>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*) {
    T value = *first;
    while (++first != last) {
        T tmp = *first;
        *++result = tmp - value;
        value = tmp;
    }
    return ++result;
}

template <class InputIterator, class OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result) {
    if (first == last) return result;
    *result = *first;
    return __adjacent_difference(first, last, result, value_type(first));
}
template <class InputIterator, class OutputIterator, class T, class BinaryFunc>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*,
                                     BinaryFunc func) {
    T value = *first;
    while (++first != last) {
        T tmp = *first;
        *++result = func(tmp, value);
        value = tmp;
    }
    return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryFunc>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryFunc func) {
    if (first == last) return result;
    *result = *first;
    return __adjacent_difference(first, last, result, value_type(first), func);
}

// [first,last) value, value+1, value+2...
template <class ForwardIter, class T>
void iota(ForwardIter first, ForwardIter last, T value) {
    while (first != last) *first++ = value++;
}
}

#endif
