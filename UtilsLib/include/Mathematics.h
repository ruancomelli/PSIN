#ifndef MATHEMATICS_H
#define MATHEMATICS_H

// boost
#include <boost/math/constants/constants.hpp>

#define M_E boost::math::constants::e<double>()
#define M_PI boost::math::constants::pi<double>()

// factorial:
//	Calculates n!, where n is a nonnegative integer
unsigned long factorial( const unsigned n );

#endif