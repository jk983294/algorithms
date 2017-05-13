#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include "pair.h"

template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const ktl::pair<T, U>& p) {
    out << "[" << p.first << ", " << p.second << "]";
    return out;
}
template <template <typename, typename> class ContainerType, typename ValueType, typename AllocType>
void display(const ContainerType<ValueType, AllocType>& c) {
    for (const auto& v : c) std::cout << v << ' ';
    std::cout << std::endl;
}
template <template <typename, typename...> class ContainerType, typename ValueType, typename... Args>
void display(const ContainerType<ValueType, Args...>& c) {
    for (const auto& v : c) std::cout << v << ' ';
    std::cout << std::endl;
}

#endif
