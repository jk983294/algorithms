#ifndef _ALGORITHM_FIND_H_
#define _ALGORITHM_FIND_H_

#include <cassert>
#include <cstring>
#include "../iterator/iterator.h"
#include "../iterator/typetraits.h"

namespace ktl {

//********** [find] *************************
template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T &val) {
    for (; first != last; ++first) {
        if (*first == val) break;
    }
    return first;
}
}

#endif
