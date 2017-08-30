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

} // psin

#endif
