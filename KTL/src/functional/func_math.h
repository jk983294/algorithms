#ifndef _FUNC_MATH_H_
#define _FUNC_MATH_H_

#include "func_common.h"

namespace ktl {

template <class T>
struct plus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x + y; }
};
template <class T>
struct minus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x - y; }
};
template <class T>
struct multiply : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x * y; }
};
template <class T>
struct divide : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x / y; }
};
template <class T>
struct module : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x % y; }
};
template <class T>
struct negate : public unary_function<T, T> {
    T operator()(const T& x) const { return -x; }
};
}

#endif
