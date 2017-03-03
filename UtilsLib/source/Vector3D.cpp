#include <Vector3D.h>

// Standard
#include <iostream>

Vector3D::Vector3D( void ){
	this->components[ X ] = 0.0;
	this->components[ Y ] = 0.0;
	this->components[ Z ] = 0.0;
}

Vector3D::Vector3D( const double& x, const double& y, const double& z ){
	this->components[ X ] = x;
	this->components[ Y ] = y;
	this->components[ Z ] = z;
}

double Vector3D::x() const{
	return this->components[ X ];
}

double Vector3D::y() const{
	return this->components[ Y ];
}

double Vector3D::z() const{
	return this->components[ Z ];
}

double& Vector3D::x(){
	return this->components[ X ];
}

double& Vector3D::y(){
	return this->components[ Y ];
}

double& Vector3D::z(){
	return this->components[ Z ];
}

double Vector3D::getComponent( const int pos ) const
{
	return this->components[pos];
}

double Vector3D::length() const
{
	return sqrt( 
		this->components[ X ]*this->components[ X ]
		+ this->components[ Y ]*this->components[ Y ]
		+ this->components[ Z ]*this->components[ Z ] 
	);
}

double Vector3D::squaredLength() const
{
	return ( 
		this->components[ X ]*this->components[ X ]
		+ this->components[ Y ]*this->components[ Y ]
		+ this->components[ Z ]*this->components[ Z ] 
	);
}

void Vector3D::normalize(){
	double invLength = 1.0/this->length();
	for( auto& component : this->components )
	{
		component *= invLength;
	}
}

double Vector3D::dist( const Vector3D& v ) const
{
	double dist = 0.0;
	for( int i = 0; i < N_AXIS; ++i ){
		dist += ( this->components[ i ] - v.components[ i ] )*
			( this->components[ i ] - v.components[ i ] );
	}
	return sqrt( dist );
}

void Vector3D::print() {
	std::cout << this->x() << ", " << this->y() << ", " << this->z() << ";" << std::endl; 
}

Vector3D Vector3D::operator +=( const Vector3D& v ){
	for( int i = 0; i < N_AXIS; ++i ){
		this->components[ i ] += v.components[ i ];
	}
	return *this;
}

Vector3D Vector3D::operator -=( const Vector3D& v ){
	for( int i = 0; i < N_AXIS; ++i ){
		this->components[ i ] -= v.components[ i ];
	}
	return *this;
}

Vector3D Vector3D::operator *=( const double scalar ){
	for( auto& component : this->components )
	{
		component *= scalar;
	}

	return *this;
}

Vector3D Vector3D::operator /=( const double scalar ){
	for( auto& component : this->components )
	{
		component /= scalar;
	}

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