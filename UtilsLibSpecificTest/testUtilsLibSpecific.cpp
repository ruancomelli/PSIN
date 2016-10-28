#define BOOST_TEST_MODULE TestModule

// std
#include <string>
#include <iostream>

// boost
#include <Test.h>
#include <Foreach.h>

// our code
#include <Vector3D.h>
#include <Vector.h>

TestCase( CheckEqualAndCheckClose )
{
	double i = 0;
	double j = 0;
	checkClose( i , j , 1.0e-12 );
	checkEqual( i , j );
}

TestCase( ForEach )
{
	DoubleVector intVector(3,0);
	foreach(double i, intVector){
		double j = 0;
		checkClose(j , i , 1.0e-12);
	}
}

TestCase( Vector3DTest )
{
	// Passing threee parameters to constructor
	double 		x1 = 1.0;
	double 		y1 = 2.0;
	double 		z1 = 3.0;
	Vector3D 	first(x1, y1, z1);

	checkEqual( first.x() , x1 );
	checkEqual( first.y() , y1 );
	checkEqual( first.z() , z1 );

	double		def = 0.0;
	double 		x2 = 4.0;
	double 		y2 = 5.0;
	double 		z2 = 6.0;
	Vector3D 	second;
	
	// Default values
	checkEqual( second.y() , def );
	checkEqual( second.x() , def );
	checkEqual( second.z() , def );

	second.x() = x2;
	second.y() = y2;
	second.z() = z2;
	
	// Values set
	checkEqual( second.x() , x2 );
	checkEqual( second.y() , y2 );
	checkEqual( second.z() , z2 );
}
