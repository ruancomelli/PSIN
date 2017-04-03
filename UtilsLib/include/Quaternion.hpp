#ifndef QUATERNION_H
#define QUATERNION_H

// UtilsLib
#include <boost/math/quaternion.hpp>

template<typename ... Ts>
using Quaternion = boost::math::quaternion<Ts ...>;

#endif
