#define BOOST_TEST_MODULE TestModule

// std
#include <string>
#include <iostream>

// boost
#include <Test.h>

// our code
#include <Vector3D.h>
#include <Vector.h>

TestCase( TestModule ){
	checkClose( -9 , -10. , 1.0e-12 );
}