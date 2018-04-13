#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <new>
#include "../iterator/typetraits.h"

namespace ktl {
template <class T1, class T2>
inline void construct(T1 *ptr1, const T2 &value) {
    new (ptr1) T1(value);  // placement new
}

template <class T>
inline void destroy(T *ptr) {
    ptr->~T();
}

// no action for POD
template <class ForwardIterator>
inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type) {}

template <class ForwardIterator>
inline void _destroy(ForwardIterator first, ForwardIterator last, _false_type) {
    for (; first != last; ++first) {
        destroy(&*first);
    }
}

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
    typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD;
    _destroy(first, last, is_POD());
}

// specilization for char* wchar_t*
inline void destroy(char *, char *) {}
inline void destroy(wchar_t *, wchar_t *) {}
}

#endif
