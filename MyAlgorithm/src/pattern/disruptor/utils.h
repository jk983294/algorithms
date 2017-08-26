#ifndef DISRUPTOR_UTILS_H_
#define DISRUPTOR_UTILS_H_

// From Google C++ Standard, modified to use C++11 deleted functions.
// A macro to disallow the copy constructor and operator= functions.
#define DISALLOW_COPY_MOVE_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&) = delete;         \
    TypeName(const TypeName&&) = delete;        \
    void operator=(const TypeName&) = delete

#endif
