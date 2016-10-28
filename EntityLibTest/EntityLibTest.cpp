#define BOOST_TEST_MODULE EntityLibTest

// UtilsLib
#include <Test.h>
#include <Foreach.h>

// EntityLib
#include <Entity.h>

TestCase( EntityTest )
{
	Entity entity1;

	// Test the default handle and the getHandle function
	int defaultHandle = -1;
	checkEqual( entity1.getHandle() , defaultHandle );

	// Test the setHandle function
	int handleToSet = 2;
	entity1.setHandle(handleToSet);
	checkEqual( entity1.getHandle() , handleToSet );
	// Test constructor passing one argument
	int initialHandle = 1;
	Entity entity2(initialHandle);
	checkEqual( entity2.getHandle() , initialHandle );
}
