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

TestCase( PhysicalEntityDefaultConstructor )
{
	// Default Constructor
	// Properties allocator not tested
	PhysicalEntity 		physicalEntity;
	int 				defaultTaylorOrder 	= 3;
	int 				defaultSize 		= defaultTaylorOrder + 1;
	int 				defaultDimension 	= 3;
	int					defaultHandle		= -1;

	vector<Vector3D> 	defaultPosition 	= physicalEntity.getPosition();
	vector<Vector3D> 	defaultOrientation 	= physicalEntity.getOrientation();
	
	checkEqual( physicalEntity.getHandle() , defaultHandle );
	checkEqual( defaultPosition.size() , defaultSize );
	checkEqual( defaultOrientation.size() , defaultSize );
	checkEqual( physicalEntity.getDimension() , defaultDimension );

}

TestCase( PhysicalEntityConstructorWithParametes )
{
	int taylorOrder	= 2;
	int size		= taylorOrder + 1;
	int dimension	= 2;
	int handle		= 5;

	// Constructor with non-default parameters
	// Properties allocator not tested
	PhysicalEntity physicalEntity(taylorOrder, dimension, handle);

	vector<Vector3D> 	position 		= physicalEntity.getPosition();
	vector<Vector3D> 	orientation 	= physicalEntity.getOrientation();

	checkEqual( physicalEntity.getHandle() , handle );
	checkEqual( position.size() , size );
	checkEqual( orientation.size() , size );
	checkEqual( physicalEntity.getDimension() , dimension );
	
}

TestCase( SpacialSetFunctions )
{

	int taylorOrder	= 4;
	int dimension	= 3;
	int handle		= 0;
	PhysicalEntity physicalEntity(taylorOrder, dimension, handle);

	// setPosition
	{
	double x = -5.4;
	double y = 8.3;
	double z = -1.7;
	int derivative = 0;
	Vector3D pos0(x , y , z);
	physicalEntity.setPosition(derivative, x, y, z);
	check( pos0==physicalEntity.getPosition(0) );
	}


}
