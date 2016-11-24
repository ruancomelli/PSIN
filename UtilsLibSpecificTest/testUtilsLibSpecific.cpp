#define BOOST_TEST_MODULE TestModule

// std
#include <string>
#include <iostream>
#include <fstream>

// boost
#include <Test.h>
#include <Foreach.h>

// our code
#include <Vector3D.h>
#include <Vector.h>

TestCase( CheckEqualAndCheckClose ){
	double i = 0;
	double j = 0;

	checkClose( i , j , 1.0e-12 );
	checkEqual( i , j );
}

TestCase( ForeachTest ){
	DoubleVector values;
	int nValues = 5;
	double rawValues[] = { 2.71, 3.14, 0.0, -3.14, -2.71 };

	for( int i = 0; i < nValues; ++i ){
		values.push_back( rawValues[ i ] );
	}

	int counter = 0;
	foreach( double v, values ){
		checkClose( rawValues[ counter ], v, 1.0e-12 );
		++counter; 
	}
}

//DoubleVector and DoubleVector2D

TestCase( DoubleVectorScalarOperatorTest ){
	DoubleVector u( 3, 0.0 );
	u[0] = 1.;
	u[1] = 2.;
	u[2] = -4.;

	double scalar = 2.5;

	DoubleVector B = scalar*u;  

	checkClose( B[0] , 2.5 , 1.0e-12 );
	checkClose( B[1] , 5. , 1.0e-12 );
	checkClose( B[2] , -10. , 1.0e-12 );
}

TestCase( DoubleVectorPlusEqualLessEqualTimesEqualOperators ){
	DoubleVector v1(2,0);
	v1[0] = -2.0;
	v1[1] = +3.0;

	DoubleVector v2(2,0);
	v2[0] = +2.0;
	v2[1] = -4.0;

	DoubleVector v3(2,0);
	v3[0] = +3.0;
	v3[1] = +5.0;

	// operator +=
	v1 += v2;
	checkClose(v1[0] , 0.0 , 1.0e-12);
	checkClose(v1[1] , -1.0 , 1.0e-12);

	// operator -=
	v2 -= v3;
	checkClose(v2[0] , -1.0 , 1.0e-12);
	checkClose(v2[1] , -9.0 , 1.0e-12);

	// operator *=
	v3 *= 5;
	checkClose(v3[0] , 15.0 , 1.0e-12);
	checkClose(v3[1] , 25.0 , 1.0e-12);
}

TestCase( DoubleVector2DDoubleVectorProductOperatorTest ){
	DoubleVector2D A( 2, DoubleVector( 2, 0.0 ) );
	A[0][0] = 4.;  A[0][1] = 3.;
	A[1][0] = -4.;  A[1][1] = 1.;

	DoubleVector B( 2, 0.0 );
	B[0] = 1.;
	B[1] = 6.;

	DoubleVector C = A*B;
	checkClose( C[0] , 22. , 1.0e-12 );
	checkClose( C[1] , 2. , 1.0e-12 );
}

TestCase( DoubleVector2DScalarOperatorTest ){
	DoubleVector2D A( 2, DoubleVector( 2, 0.0 ) );
	A[0][0] = 1.;
	A[0][1] = 2.;
	A[1][0] = -4.;
	A[1][1] = -3.;

	double scalar = 2.0;

	DoubleVector2D B = scalar*A;  
	checkClose( B[0][0] , 2. , 1.0e-12 );
	checkClose( B[0][1] , 4. , 1.0e-12 );
	checkClose( B[1][0] , -8. , 1.0e-12 );
	checkClose( B[1][1] , -6. , 1.0e-12 );
}

TestCase( DoubleVector2DInnerProductOperatorTest ){
	DoubleVector2D A( 2, DoubleVector( 3, 0.0 ) );
	A[0][0] = 3.;  A[0][1] = 1.;  A[0][2] = 2.;
	A[1][0] = 5.;  A[1][1] = 8.;  A[1][2] = 3.;

	DoubleVector2D B( 3, DoubleVector( 2, 0.0 ) );
	B[0][0] = 3.;  B[0][1] = 1.;
	B[1][0] = 4.;  B[1][1] = 4.;
	B[2][0] = 5.;  B[2][1] = 8.;

	DoubleVector2D C = A*B;
	checkClose( C[0][0] , 23. , 1.0e-12 );
	checkClose( C[0][1] , 23. , 1.0e-12 );
	checkClose( C[1][0] , 62. , 1.0e-12 );
	checkClose( C[1][1] , 61. , 1.0e-12 );
}

TestCase( InnerProductOperator ){
	DoubleVector v1( 3 , 0 );
	v1[0] = +2.0;
	v1[1] = -3.0;
	v1[2] = +4.0;

	DoubleVector v2( 3 , 0 );
	v2[0] = -5.0;
	v2[1] = -9.0;
	v2[2] = +7.0;

	double inner = innerProduct(v1, v2);
	checkClose( inner, +45.0 , 1.0e-12 );
}

TestCase( NormOperator ){
	DoubleVector v1( 3 , 0 );
	v1[0] = +2.0;
	v1[1] = -3.0;
	v1[2] = +4.0;

	double nor = norm(v1);
	checkClose( nor, +5.385164807 , 1.0e-8 );
}

TestCase( NormalizeOperator ){
	DoubleVector v1( 3 , 0 );
	v1[0] = +2.0;
	v1[1] = -3.0;
	v1[2] = +4.0;

	normalize(v1);
	checkClose( v1[0], +0.371390676354104 , 1.0e-12 );
	checkClose( v1[1], -0.557086014531156 , 1.0e-12 );
	checkClose( v1[2], +0.742781352708207 , 1.0e-12 );
}

TestCase( NullVectorTest ){
	DoubleVector null = nullVector(5);

	foreach(double d, null){
		checkEqual( d , 0.0 );
	}
}

//Vector3D

TestCase( Vector3DInitializationTest ){

	// Default constructor
	Vector3D v0;
	checkEqual( 0.0 , v0.x() );
	checkEqual( 0.0 , v0.y() );
	checkEqual( 0.0 , v0.z() );

	// Passig three arguments to constructor
	Vector3D v1(1.0 , 2.0 , 3.0 );
	checkEqual( 1.0 , v1.x() );
	checkEqual( 2.0 , v1.y() );
	checkEqual( 3.0 , v1.z() );

	// Passig a vector to constructor
	Vector3D v2( v1 );
	checkEqual( 1.0 , v2.x() );
	checkEqual( 2.0 , v2.y() );
	checkEqual( 3.0 , v2.z() );
}

TestCase( Vector3DFunctionsMembers ){
	Vector3D v1( 1.0 , 2.0 , 3.0 );

	//Vector3D::getComponent()
	for(int i=0 ; i<3 ; ++i){
		checkEqual( i+1 , v1.getComponent(i) );
	}

	//Vector3D::length()
	double len = v1.length();
	checkClose(len , 3.74165738677394 , 1.0e-8 );

	//Vector3D::squareLength()
	double sqrlen = v1.squaredLength();
	checkClose(sqrlen , 14.0 , 1.0e-8 );

	//Vector3D::normalize()
	v1.normalize();
	checkClose( v1.x(), +0.267261241912424 , 1.0e-12 );
	checkClose( v1.y(), +0.534522483824849 , 1.0e-12 );
	checkClose( v1.z(), +0.801783725737273 , 1.0e-12 );
}

TestCase( TestVector3D ){
	Vector3D v0( 1.0, 1.5, 2.0 );
	checkEqual( 1.0, v0.x() );
	checkEqual( 1.5, v0.y() );
	checkEqual( 2.0, v0.z() );

	Vector3D v1( 1.0, 1.0, 1.0 );

	v0 += v1;
	checkEqual( 2.0, v0.x() );
	checkEqual( 2.5, v0.y() );
	checkEqual( 3.0, v0.z() );

	v0-=v1;
	checkEqual( 1.0, v0.x() );
	checkEqual( 1.5, v0.y() );
	checkEqual( 2.0, v0.z() );

	v0*=2.0;
	checkEqual( 2.0, v0.x() );
	checkEqual( 3.0, v0.y() );
	checkEqual( 4.0, v0.z() );

	v0/=4.0;
	checkEqual( 0.5, v0.x() );
	checkEqual( 0.75, v0.y() );
	checkEqual( 1.0, v0.z() ); 
}

TestCase( Vector3DCroosDotTriple ){
	Vector3D v1( 4.0 , 2.0 , 7.0 );
	Vector3D v2( 4.0 , 5.0 , 9.0 );
	Vector3D v3( 1.0 , 8.0 , 3.0 );

	// cross
	Vector3D t1 = cross( v1 , v2 );
	checkEqual( t1.x() , -17.0 );
	checkEqual( t1.y() , -8.0 );
	checkEqual( t1.z() , 12.0 );

	// dot
	double inner = dot( v1 , v2 );
	checkEqual( inner , 89.0 );

	// triple
	double trip = triple( v1 , v2 , v3 );
	checkEqual( trip , -45.0 );
}

TestCase( Vector3DIsEqualOperator ){
	Vector3D v1( 1.0 , -3.4 , 2.5 );
	Vector3D v2( 1.0 , -3.4 , 2.5 );
	Vector3D v3( 1.0 , -3.4 , 9.0 );

	checkEqual( v1==v2 , true );
	checkEqual( v1==v3 , false );
	checkEqual( nullVector3D()==nullVector3D() , true );

}

TestCase( VectorInput ){
	std::ifstream file("input.txt");

	vector<int> tester(5);
		tester[0] = 3;
		tester[1] = 1;
		tester[2] = 4;
		tester[3] = 1;
		tester[4] = 5;

	vector<int> tested(5);

	/* YOUR JOB IS TO ALLOW ME TO DO THE FOLLOWING: */
	// file >> tested;
	// cout << tester;
	// checkEqual(tested, tester);
	//
	// THANK YOU
}
