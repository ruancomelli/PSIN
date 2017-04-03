#ifndef VECTOR_H
#define VECTOR_H

// Standard
#include <vector>


using std::vector;


typedef vector< double > DoubleVector;
typedef vector< DoubleVector > DoubleVector2D;


// DoubleVector Basic Operations
DoubleVector operator *(const double & scalar, DoubleVector vec);
DoubleVector operator *(const DoubleVector & vec, const double & scalar);
DoubleVector operator -=( DoubleVector& v, const double& d );
DoubleVector operator +=( DoubleVector& v, const double& d );
void operator +=( DoubleVector& vector1, const DoubleVector& vector2 );
void operator -=( DoubleVector& vector1, const DoubleVector& vector2 );
void operator *=( DoubleVector& vec, const double& scalar );

// DoubleVector2D Basic operations
void operator +=( DoubleVector2D& mat1, const DoubleVector2D& mat2 );
DoubleVector	operator *( const DoubleVector2D & A, const DoubleVector & vector );
DoubleVector2D	operator *( const double scalar, DoubleVector2D matrix );
DoubleVector2D	operator *( const DoubleVector2D & A, const DoubleVector2D & B );

// Vectorial Operations
double innerProduct( const DoubleVector& vector1, const DoubleVector & vector2 );
double norm( DoubleVector& vec );
void normalize( DoubleVector& vec );

DoubleVector nullVector(int dimension);

template <class type> 
bool operator==( vector<type> & left , vector<type> & right );
template <class type> 
bool operator!=( vector<type> & left , vector<type> & right );

#include <Vector.tpp>

#endif
