#ifndef MATHEMATICS_HPP
#define MATHEMATICS_HPP

// boost
#include <boost/math/constants/constants.hpp>

#ifndef M_E
#define M_E boost::math::constants::e<double>()
#endif

#ifndef M_PI
#define M_PI boost::math::constants::pi<double>()
#endif

namespace psin {
	
// factorial:
//	Calculates n!, where n is a nonnegative integer
unsigned long factorial( const unsigned n );

} // psin

#endif
