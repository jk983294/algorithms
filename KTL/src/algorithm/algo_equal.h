#ifndef _ALGORITHM_COPY_H_
#define _ALGORITHM_COPY_H_

#include <cassert>
#include <cstring>
#include "../iterator/iterator.h"
#include "../iterator/typetraits.h"

namespace ktl {

template <class InputIterator, class InputIterator1>
bool equal(InputIterator first1, InputIterator last1, InputIterator1 first2) {
    while (first1 != last1) {
        if (*first1 != *first2) return false;
        ++first1;
        ++first2;
    }
    return true;
}
}

#endif
