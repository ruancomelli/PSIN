#ifndef SFINAE_TRUE_HPP
#define SFINAE_TRUE_HPP

// Standard
#include <type_traits>

template<typename...>
struct sfinae_true : std::true_type {};

#endif