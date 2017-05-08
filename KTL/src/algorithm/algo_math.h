#ifndef _ALGORITHM_MATH_H_
#define _ALGORITHM_MATH_H_

#include <cassert>
#include <cstring>
#include "../iterator/iterator.h"
#include "../iterator/typetraits.h"

namespace ktl {

template <class T>
T max(T a, T b) {
    return a > b ? a : b;
}

template <class T>
T min(T a, T b) {
    return a < b ? a : b;
}
}

#endif
