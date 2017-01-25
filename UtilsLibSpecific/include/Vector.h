#ifndef VECTOR_H
#define VECTOR_H

// Standard
#include <numeric>
#include <vector>
#include <list>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>


using std::vector;
using std::list;
using std::set;
using std::runtime_error;

	typedef vector< double > DoubleVector;
	typedef vector< DoubleVector > DoubleVector2D;

	// DoubleVector Basic Operations
	DoubleVector operator *(const double & scalar, const DoubleVector vec);
	DoubleVector operator *(const DoubleVector vec, const double & scalar);
	DoubleVector operator -=( DoubleVector& v, const double& d );
	DoubleVector operator +=( DoubleVector& v, const double& d );
	void operator +=( DoubleVector& vector1, const DoubleVector& vector2 );
	void operator -=( DoubleVector& vector1, const DoubleVector& vector2 );
	void operator *=( DoubleVector& vec, const double& scalar );

	// DoubleVector2D Basic operations
	void operator +=( DoubleVector2D& mat1, const DoubleVector2D& mat2 );
	DoubleVector	operator *( const DoubleVector2D & A, const DoubleVector & vector );
	DoubleVector2D	operator *( const double& scalar, const DoubleVector2D & matrix );
	DoubleVector2D	operator *( const DoubleVector2D & A, const DoubleVector2D & B );

	// Vectorial Operations
	double innerProduct( const DoubleVector& vector1, const DoubleVector& vector2 );
	double norm( DoubleVector& vec );
	void normalize( DoubleVector& vec );

	DoubleVector nullVector(int dimension);


	template <class type> std::ostream & operator<<( std::ostream & outputFile , const vector<type> & v){
		for( int i = 0 ; i < v.size() ; ++i){
			outputFile << static_cast<type>(v[i]) << endl;
		}

		return outputFile;
	}

	template <class type> std::istream & operator>>( std::istream & inputFile , vector<type> & v){
		for( int i = 0 ; ( i < v.size() ) && ( !inputFile.eof() ) ; ++i){
			inputFile >> v[i];
		}

		return inputFile;
	}

	template <class type> std::ofstream & operator<<( std::ofstream & outputFile , const vector<type> & v){
		for( int i = 0 ; i < v.size() &&  ; ++i){
			outputFile << static_cast<type>(v[i]) << endl;
		}

		return outputFile;
	}

	template <class type> std::ifstream & operator>>( std::ifstream & inputFile , vector<type> & v){
		for( unsigned i = 0 ; ( i < v.size() ) && ( !inputFile.eof() ) ; ++i){
			inputFile >> v[i];
		}

		return inputFile;
	}

	template <class type> bool operator==( vector<type> & left , vector<type> & right ){

		if( left.size() == right.size() )
		{
			for( int i = 0 ; i < left.size() ; ++i ){
				if( left[i] != right[i] ) return false;
			}
		}
		else
		{
			return false;
		}

		return true;
	}

#endif
