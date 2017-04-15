#ifndef MATHEMATICS_H
#define MATHEMATICS_H

// boost
#include <boost/math/constants/constants.hpp>

#ifndef M_E
#define M_E boost::math::constants::e<double>()
#endif

#ifndef M_PI
#define M_PI boost::math::constants::pi<double>()
#endif

// factorial:
//	Calculates n!, where n is a nonnegative integer
unsigned long factorial( const unsigned n );

#endif
