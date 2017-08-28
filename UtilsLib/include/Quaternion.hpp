#ifndef QUATERNION_HPP
#define QUATERNION_HPP

// UtilsLib
#include <boost/math/quaternion.hpp>

namespace psin {
	
template<typename ... Ts>
using Quaternion = boost::math::quaternion<Ts ...>;

} // psin

#endif //QUATERNION_HPP
