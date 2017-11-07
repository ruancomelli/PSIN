#ifndef QUATERNION_HPP
#define QUATERNION_HPP

// UtilsLib
#include <Eigen/Geometry>
#include <Vector3D.hpp>

#include <json.hpp>

namespace psin {

using namespace Eigen;

Quaterniond operator+(Quaterniond lhs, const Quaterniond & rhs);
Quaterniond operator-(Quaterniond lhs, const Quaterniond & rhs);
Quaterniond& operator+=(Quaterniond & lhs, const Quaterniond & rhs);
Quaterniond& operator-=(Quaterniond & lhs, const Quaterniond & rhs);
Quaterniond operator*(const double d, Quaterniond q);
Quaterniond operator*(const Quaterniond & q, const double d);
Quaterniond toQuaterniond(const Vector3D & v);

} // psin

namespace Eigen
{
	using json = nlohmann::json;
	using Quaterniond = ::Eigen::Quaterniond;
	
	void to_json(json& j, const Quaterniond& q);
	void from_json(const json& j, Quaterniond& q);
}

#endif //QUATERNION_HPP
