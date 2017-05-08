#ifndef _ALGORITHM_FILL_H_
#define _ALGORITHM_FILL_H_

#include <cassert>
#include <cstring>
#include "../iterator/iterator.h"
#include "../iterator/typetraits.h"

namespace ktl {

//***** fill O(N)******
template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T &value) {
    for (; first != last; ++first) *first = value;
}

inline void fill(char *first, char *last, const char &value) {
    memset(first, static_cast<unsigned char>(value), last - first);
}

inline void fill(wchar_t *first, wchar_t *last, const wchar_t &value) {
    memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
}

//***** fill_n O(N)******
template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T &value) {
    for (; n > 0; --n, ++first) *first = value;
    return first;
}

template <class Size>
char *fill_n(char *first, Size n, const char &value) {
    memset(first, static_cast<unsigned char>(value), n);
    return first + n;
}

template <class Size>
wchar_t *fill_n(wchar_t *first, Size n, const wchar_t &value) {
    memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
    return first + n;
}
}

#endif
