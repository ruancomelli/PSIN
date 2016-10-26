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