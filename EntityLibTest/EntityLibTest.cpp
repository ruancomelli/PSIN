#define BOOST_TEST_MODULE EntityLibTest

// UtilsLib
#include <Mathematics.h>
#include <Vector3D.h>
#include <Vector.h>
#include <Test.h>
#include <Foreach.h>

// EntityLib
#include <Entity.h>
#include <PhysicalEntity.h>

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

TestCase( PhysicalEntityTest )
{
	// Default Constructor
	PhysicalEntity 		physicalEntity0;
	int 				defaultTaylorOrder 	= 3;
	int 				defaultSize 		= defaultTaylorOrder + 1;
	int 				defaultDimension 	= 3;
	vector<Vector3D> 	defaultPosition 	= physicalEntity0.getPosition();
	vector<Vector3D> 	defaultOrientation 	= physicalEntity0.getOrientation();

	checkEqual( defaultPosition.size() , defaultSize );
	checkEqual( defaultOrientation.size() , defaultSize );

}
