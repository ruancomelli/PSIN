#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

#define VECTOR_3D_EQUAL_TOLERANCE 1e-12

// JSONLib
#include <json.hpp>

#include <Eigen/Core>

#include <array>

namespace psin {

using Vector3D = Eigen::Vector3d;

// class Vector3D{
// public:
// 	Vector3D();
// 	explicit Vector3D( const double& x );
// 	Vector3D( const double& x, const double& y, const double& z=0.0 );

// 	double x() const;
// 	double y() const;
// 	double z() const;
// 	double& x();
// 	double& y();
// 	double& z();
// 	double length() const;
// 	double squaredLength() const;
// 	void normalize();
// 	Vector3D normalized() const;
// 	double dist( const Vector3D& v ) const;
// 	double operator[](const std::size_t & pos) const;
// 	double& operator[](const std::size_t & pos);
// 	Vector3D operator +=( const Vector3D& v );
// 	Vector3D operator -=( const Vector3D& v );
// 	Vector3D operator *=( const double scalar );
// 	Vector3D operator /=( const double scalar );
// 	void print() const;
// 	Vector3D projectOn(const Vector3D & v) const;

// 	virtual ~Vector3D() = default;

// protected:
// 	std::array<double, 3> components;
// };

template<typename Out>
Out& operator<<(Out& out, const Vector3D & v) noexcept 
{
	return out << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
}

Vector3D cross( const Vector3D& v0, const Vector3D& v1 );
double dot( const Vector3D& v0, const Vector3D& v1 );
double triple( const Vector3D& v0, const Vector3D& v1, const Vector3D& v2 );
Vector3D operator -( const Vector3D& v0, const Vector3D& v1 );
Vector3D operator +( const Vector3D& v0, const Vector3D& v1 );
Vector3D operator *( const double scalar, const Vector3D& v );
Vector3D operator *( const Vector3D& v, const double scalar );
Vector3D operator /( const Vector3D& v, const double scalar );
Vector3D operator - (const Vector3D& v);
bool operator == ( const Vector3D & v1 , const Vector3D & v2 );
bool operator != ( const Vector3D & v1 , const Vector3D & v2 );
double distance(const Vector3D & left, const Vector3D & right);

inline Vector3D nullVector3D(void){ return Vector3D(); }

Vector3D projectOn(const Vector3D & lhs, const Vector3D & rhs);

} // psin

namespace Eigen
{
	using json = nlohmann::json;
	using Vector3d = ::Eigen::Vector3d;
	
	void to_json(json& j, const Vector3d& v);
	void from_json(const json& j, Vector3d& v);
}

#endif // VECTOR_3D_HPP
