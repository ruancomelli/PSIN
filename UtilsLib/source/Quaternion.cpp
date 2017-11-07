#ifndef QUATERNION_CPP
#define QUATERNION_CPP

// UtilsLib
#include <Quaternion.hpp>

namespace psin {

Quaterniond operator+(Quaterniond lhs, const Quaterniond & rhs)
{
	lhs.coeffs() += rhs.coeffs();
	return lhs;
}

Quaterniond operator-(Quaterniond lhs, const Quaterniond & rhs)
{
	lhs.coeffs() -= rhs.coeffs();
	return lhs;
}

Quaterniond& operator+=(Quaterniond & lhs, const Quaterniond & rhs)
{
	lhs.coeffs() += rhs.coeffs();
	return lhs;
}

Quaterniond& operator-=(Quaterniond & lhs, const Quaterniond & rhs)
{
	lhs.coeffs() -= rhs.coeffs();
	return lhs;
}

Quaterniond operator*(const double d, Quaterniond q)
{
	q.coeffs() *= d;
	return q;
}
Quaterniond operator*(const Quaterniond & q, const double d)
{
	return d * q;
}

Quaterniond toQuaterniond(const Vector3D & v)
{
	return Quaterniond(0, v.x(), v.y(), v.z());
}

} // psin

namespace Eigen
{	
	void to_json(json& j, const Quaterniond& q)
	{
		j = json{
			q.w(),
			q.x(),
			q.y(),
			q.z()
		};
	}

	void from_json(const json& j, Quaterniond& q)
	{
		switch(j.size())
		{
			case 1:
				q = Quaterniond(j.at(0), 0, 0, 0);
				break;
			case 3:
				q = Quaterniond(0, j.at(0), j.at(1), j.at(2));
				break;
			default:
				q = Quaterniond(j.at(0), j.at(1), j.at(2), j.at(3));
		}
	}
}

#endif //QUATERNION_CPP
