#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

#define VECTOR_3D_EQUAL_TOLERANCE 1e-12

#include <array>

namespace psin {

class Vector3D{
public:
	Vector3D( void );
	explicit Vector3D( const double& x, const double& y=0.0, const double& z=0.0 );

	double x() const;
	double y() const;
	double z() const;
	double& x();
	double& y();
	double& z();
	double length() const;
	double squaredLength() const;
	void normalize();
	Vector3D normalized() const;
	double dist( const Vector3D& v ) const;
	double operator[](const std::size_t & pos) const;
	double& operator[](const std::size_t & pos);
	Vector3D operator +=( const Vector3D& v );
	Vector3D operator -=( const Vector3D& v );
	Vector3D operator *=( const double scalar );
	Vector3D operator /=( const double scalar );
	void print() const;


	virtual ~Vector3D(){}

protected:
	std::array<double, 3> components;
};

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

} // psin

#endif // VECTOR_3D_HPP
