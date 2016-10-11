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
	

//Set vector with values

	template <typename type>
	void setVector(vector <type> & vec, const type * const values){
		for(int i = 0; i < vec.size(); ++i){
			vec[i] = values[i];
		}
	}

		template <typename type>
	void setVector(vector <type> & vec, const type * values, int size){
		vec.resize(size, 0);
		for(int i = 0; i < size; ++i){
			vec[i] = values[i];
		}
	}
	template <typename type>
	vector <type> setVector(const type * values, int size){
		vector <type> vec(values, values + size - 1);
		return vec;
	}
	
	template <typename type>
	void setVector2D(vector < vector <type> > & vec, const type *values){
		for(int i = 0; i < vec.size(); ++i){
			for(int j = 0; j < vec[i].size(); ++j){
				vec[i][j] = *(values + i*vec.size() + j);
			}
		}
	}
	template <typename type>
	void setVector2D(vector < vector <type> > & vec, const type *values, int size1, int size2){
		vec.resize(size1);
		for(int i = 0; i < size1; ++i){
			vec[i].resize(size2);
			for(int j = 0; j < size2; ++j){
				vec[i][j] = *(values + i*vec.size() + j);
			}
		}
	}
	template <typename type>
	vector < vector <type> > setVector2D(const type *values, int size1, int size2){
		vector < vector <type> > vec;
		vec.resize(size1);
		
		for(int i = 0; i < size1; ++i){
			vec[i].resize(size2);
			for(int j = 0; j < size2; ++j){
				vec[i][j] = *(values + i*size1 + j);
			}
		}
		
		return vec;
	}


#endif
