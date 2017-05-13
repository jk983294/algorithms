#ifndef _FUNC_COMMON_H_
#define _FUNC_COMMON_H_

namespace ktl {

template <class Arg, class Result>
struct unary_function {
    typedef Arg argumant_type;
    typedef Result result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};
}

#endif
