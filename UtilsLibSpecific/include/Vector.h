#ifndef VECTOR_H
#define VECTOR_H

#include <numeric>
#include <vector>
#include <list>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <cmath>

using std::vector;
using std::list;
using std::set;
using std::runtime_error;

	typedef vector< double > DoubleVector;
	typedef vector< DoubleVector > DoubleVector2D;

	DoubleVector operator *(const double & scalar, const DoubleVector vec);
	DoubleVector operator *(const DoubleVector vec, const double & scalar);
	DoubleVector operator -=( DoubleVector& v, const double& d );
	DoubleVector operator +=( DoubleVector& v, const double& d );
	void operator +=( DoubleVector& vector1, const DoubleVector& vector2 );
	void operator -=( DoubleVector& vector1, const DoubleVector& vector2 );
	void operator *=( DoubleVector& vec, const double& scalar );	

	void operator +=( DoubleVector2D& mat1, const DoubleVector2D& mat2 );

	double innerProduct( const DoubleVector& vector1, const DoubleVector& vector2 );
	double norm( DoubleVector& vec );
	void normalize( DoubleVector& vec );
	
	template <typename type>
	vector <type> setVector(const type * values, int size);
	template <typename type>
	void setVector(vector <type> & vec, const type * values);
	template <typename type>
	void setVector(vector <type> & vec, const type * values, int size);
	
	template <typename type>
	void setVector2D(vector < vector <type> > & vec, const type *values);
	template <typename type>
	void setVector2D(vector < vector <type> > & vec, const type *values, int size1, int size2);
	template <typename type>
	vector < vector <type> > setVector2D(const type *values, int size1, int size2);


#endif
