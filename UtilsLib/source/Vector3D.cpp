#include <Vector3D.hpp>

// Standard
#include <cmath>
#include <iostream>

Vector3D::Vector3D( void ){
	this->xComponent = 0.0;
	this->yComponent = 0.0;
	this->zComponent = 0.0;
}

Vector3D::Vector3D( const double& x, const double& y, const double& z ){
	this->xComponent = x;
	this->yComponent = y;
	this->zComponent = z;
}

double Vector3D::x() const{
	return this->xComponent;
}

double Vector3D::y() const{
	return this->yComponent;
}

double Vector3D::z() const{
	return this->zComponent;
}

double& Vector3D::x(){
	return this->xComponent;
}

double& Vector3D::y(){
	return this->yComponent;
}

double& Vector3D::z(){
	return this->zComponent;
}

double Vector3D::length() const
{
	return sqrt( 
		this->xComponent * this->xComponent
		+ this->yComponent * this->yComponent
		+ this->zComponent * this->zComponent 
	);
}

double Vector3D::squaredLength() const
{
	return ( 
		this->xComponent * this->xComponent
		+ this->yComponent * this->yComponent
		+ this->zComponent * this->zComponent 
	);
}

void Vector3D::normalize(){
	double invLength = 1.0/this->length();

	xComponent *= invLength;
	yComponent *= invLength;
	zComponent *= invLength;
}

Vector3D Vector3D::normalized() const
{
	return (*this) / this->length();
}

double Vector3D::dist( const Vector3D& v ) const
{
	double dist = (*this - v).length();
	return dist;
}

void Vector3D::print() {
	std::cout << this->xComponent << ", " << this->yComponent << ", " << this->zComponent << ";" << std::endl; 
}

Vector3D Vector3D::operator +=( const Vector3D& v ){
	this->xComponent += v.xComponent;
	this->yComponent += v.yComponent;
	this->zComponent += v.zComponent;

	return *this;
}

Vector3D Vector3D::operator -=( const Vector3D& v ){
	this->xComponent -= v.xComponent;
	this->yComponent -= v.yComponent;
	this->zComponent -= v.zComponent;

	return *this;
}

Vector3D Vector3D::operator *=( const double scalar ){
	this->xComponent *= scalar;
	this->yComponent *= scalar;
	this->zComponent *= scalar;

	return *this;
}

Vector3D Vector3D::operator /=( const double scalar ){
	this->xComponent /= scalar;
	this->yComponent /= scalar;
	this->zComponent /= scalar;

	return *this;
}

Vector3D cross( const Vector3D& v0, const Vector3D& v1 ){
	return Vector3D( 
		v0.y()*v1.z() - v0.z()*v1.y(), 
		v0.z()*v1.x() - v0.x()*v1.z(), 
		v0.x()*v1.y() - v0.y()*v1.x() 
		);
}

double dot( const Vector3D& v0, const Vector3D& v1 ){
	return v0.x()*v1.x() + v0.y()*v1.y() + v0.z()*v1.z();
}

double triple( const Vector3D& v0, const Vector3D& v1, const Vector3D& v2 ){
	return dot( v0, cross( v1, v2 ) );
}

Vector3D operator -( const Vector3D& v0, const Vector3D& v1 ){
	return Vector3D( 
		v0.x() - v1.x(), 
		v0.y() - v1.y(), 
		v0.z() - v1.z() 
		);
}

Vector3D operator +( const Vector3D& v0, const Vector3D& v1 ){
	return Vector3D( 
		v0.x() + v1.x(), 
		v0.y() + v1.y(), 
		v0.z() + v1.z() 
		);
}

Vector3D operator *( const double scalar, const Vector3D& v ){
	return Vector3D( scalar*v.x(), scalar*v.y(), scalar*v.z() );
}

Vector3D operator *( const Vector3D& v, const double scalar ){
	return Vector3D( scalar*v.x(), scalar*v.y(), scalar*v.z() );
}

Vector3D operator /( const Vector3D& v, const double scalar ){
	return Vector3D( v.x()/scalar, v.y()/scalar, v.z()/scalar );
}

Vector3D operator - (const Vector3D & v){
	return Vector3D( -v.x(), -v.y(), -v.z() );
}

bool operator == ( const Vector3D & v1 , const Vector3D & v2 ){
	if( (v1.length() == 0) && (v2.length() == 0) ) return true;
	
	const double diffNormalized = (v1 - v2).length() / (v1.length() + v2.length());

	if ( diffNormalized < VECTOR_3D_EQUAL_TOLERANCE ) return true;
	else return false;
}

bool operator != ( const Vector3D & v1 , const Vector3D & v2 ){
	return ! ( v1==v2 );
}

double distance(const Vector3D & left, const Vector3D & right)
{
	return left.dist(right);
}