#ifndef MATHEMATICS_HPP
#define MATHEMATICS_HPP

// boost
#include <boost/math/constants/constants.hpp>

namespace psin {

using boost::math::constants::e;
using boost::math::constants::pi;

// factorial:
//	Calculates n!, where n is a nonnegative integer
unsigned long factorial( const unsigned n );

template <typename T> inline constexpr
int signum(T x, std::false_type is_signed) {
    return T(0) < x;
}

template <typename T> inline constexpr
int signum(T x, std::true_type is_signed) {
    return (T(0) < x) - (x < T(0));
}

template <typename T> inline constexpr
int signum(T x) {
    return signum(x, std::is_signed<T>());
}

} // psin

#endif
