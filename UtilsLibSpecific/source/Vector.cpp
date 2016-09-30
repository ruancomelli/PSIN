#include "Vector.h"

// Scalar by vector multiplication
	DoubleVector operator *(const double & scalar, const DoubleVector vec){
		DoubleVector answer(vec);
		for( DoubleVector::iterator iter = answer.begin(); iter != answer.end(); ++iter ){
			*iter *= scalar;
		}
		
		return answer;
	}
// Vector by scalar multiplication
	DoubleVector operator *(const DoubleVector vec, const double & scalar){
		return scalar * vec;
	}

	DoubleVector operator -=( DoubleVector& v, const double& d ){
		for( unsigned int i = 0; i < v.size(); ++i ){
			v[i] -= d;
		}
		return v;
	}
	
	DoubleVector operator +=( DoubleVector& v, const double& d ){
		for( unsigned int i = 0; i < v.size(); ++i ){
			v[i] += d;
		}
		return v;
	}

	double add( double a, double b ){
		return a + b;
	}

	double subtract( double a, double b ){
		return a - b;
	}

	void operator +=( DoubleVector& vector1, const DoubleVector& vector2 ){
		if( vector1.size() != vector2.size() ) {
			throw runtime_error( "DoubleVector += operator: Vectors dimensions don't agree." );
		}
		std::transform( vector1.begin(), vector1.end(), vector2.begin(), vector1.begin(), add );
	}

	void operator -=( DoubleVector& vector1, const DoubleVector& vector2 ){
		//std::transform( vector1.begin(), vector1.end(), vector2.begin(), vector1.begin(), subtract );
		for( unsigned i = 0; i < vector1.size(); ++i ){
			vector1[ i ] -= vector2[ i ];
		}
	}

	void operator *=( DoubleVector& vec, const double& scalar ){
		for( DoubleVector::iterator iter = vec.begin(); iter != vec.end(); ++iter ){
			*iter *= scalar;
		}
	}

	double innerProduct( const DoubleVector& vector1, const DoubleVector& vector2 ){
		return std::inner_product( vector1.begin(), vector1.end(), vector2.begin(), 0.0 );
	}

	double norm( DoubleVector& vec ){
		return sqrt( innerProduct( vec, vec ) );
	}

	void normalize( DoubleVector& vec ){
		vec *= 1.0/norm( vec );
	}

	void operator +=( DoubleVector2D& mat1, const DoubleVector2D& mat2 )
	{
		if( (mat1.size() != mat2.size()) || ( mat1[0].size() != mat2[0].size() ) ) {
			throw runtime_error( "DoubleVector2D += operator: matrices dimensions don't agree." );
		}
		for( unsigned i = 0 ; i < mat1.size() ; ++i ){
			std::transform( mat1[i].begin(), mat1[i].end(), mat2[i].begin(), mat1[i].begin(), add );
		}
	}
