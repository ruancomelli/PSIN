#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <vector>
#include <math.h>
#include <ostream>

using namespace std;

enum Axis{
	X, Y, Z, N_AXIS = 3
};
typedef vector< Axis > AxisArray;

class Vector3D{
public:
	Vector3D( const double& x=0.0, const double& y=0.0, const double& z=0.0 );
	Vector3D( const Vector3D& other );

	double x() const;
	double y() const;
	double z() const;
	double& x();
	double& y();
	double& z();
	double getComponent( int pos ) const;
	double length();
	double squaredLength();
	void normalize();
	double dist( const Vector3D& v );
	Vector3D operator +=( const Vector3D& v );
	Vector3D operator -=( const Vector3D& v );
	Vector3D operator *=( const double& scalar );
	Vector3D operator /=( const double& scalar );
	void print();

	virtual ~Vector3D(){}

protected:
	double components[ N_AXIS ];
}; //class Vector3D;

Vector3D cross( const Vector3D& v0, const Vector3D& v1 );
double dot( const Vector3D& v0, const Vector3D& v1 );
double triple( const Vector3D& v0, const Vector3D& v1, const Vector3D& v2 );
Vector3D operator -( const Vector3D& v0, const Vector3D& v1 );
Vector3D operator +( const Vector3D& v0, const Vector3D& v1 );
Vector3D operator *( const double& scalar, const Vector3D& v );
Vector3D operator *( const Vector3D& v, const double& scalar );
Vector3D operator /( const Vector3D& v, const double& scalar );
Vector3D operator - (const Vector3D& v);

std::ostream& operator << (std::ostream& stream, const Vector3D& v);

Vector3D nullVector3D(void);


#endif
