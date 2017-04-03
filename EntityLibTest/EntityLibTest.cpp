#define BOOST_TEST_MODULE EntityLibTest

// UtilsLib
#include <Mathematics.h>
#include <Vector3D.h>
#include <Vector.h>
#include <Test.h>
#include <Foreach.h>

// EntityLib
#include <Boundary.h>
#include <FixedInfinitePlane.h>

#include <Entity.h>
#include <PhysicalEntity.h>
#include <Particle.h>
#include <SphericalParticle.h>

// IOLib
#include <vectorIO.h>

// PropertyLib
#include <PropertyContainer.h>

using namespace std;

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

	Entity entity3 = entity1;

	checkEqual( entity1.getHandle(), entity3.getHandle() );

	int commonHandle = 7;
	Entity entity4(commonHandle);
	Entity entity5(commonHandle);

	check(entity4 == entity5);
}

TestCase( PhysicalEntityDefaultConstructor )
{
	// Default Constructor
	PhysicalEntity 		physicalEntity;
	int 				defaultTaylorOrder 	= 3;
	int 				defaultSize 		= defaultTaylorOrder + 1;
	int 				defaultDimension 	= 3;
	int					defaultHandle		= -1;
	GeometryType geometryType = DEFAULT;

	vector<Vector3D> 			defaultPosition 	= physicalEntity.getPosition();
	vector<Vector3D> 			defaultOrientation 	= physicalEntity.getOrientation();
	
	checkEqual( physicalEntity.getHandle() , defaultHandle );
	checkEqual( defaultPosition.size() , defaultSize );
	checkEqual( defaultOrientation.size() , defaultSize );
	checkEqual( physicalEntity.getDimension() , defaultDimension );
	checkEqual( physicalEntity.getGeometry(), geometryType );
}

TestCase( PhysicalEntityConstructorWithEntity )
{
	int 				defaultTaylorOrder 	= 3;
	int 				defaultSize 		= defaultTaylorOrder + 1;
	int 				defaultDimension 	= 3;
	int					handle				= 5;
	GeometryType geometryType = DEFAULT;

	Entity				entity(handle);
	
	PhysicalEntity 		physicalEntity(entity);

	vector<Vector3D> 			defaultPosition 	= physicalEntity.getPosition();
	vector<Vector3D> 			defaultOrientation 	= physicalEntity.getOrientation();
	
	checkEqual( physicalEntity.getHandle() , handle );
	checkEqual( defaultPosition.size() , defaultSize );
	checkEqual( defaultOrientation.size() , defaultSize );
	checkEqual( physicalEntity.getDimension() , defaultDimension );
	checkEqual(physicalEntity.getGeometry(), geometryType);
}

TestCase( PhysicalEntityConstructorWithParameters )
{
	int taylorOrder	= 3;
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

	// Constructor with non-default parameters, but without handle
	int defaultHandle = -1;
	PhysicalEntity physicalEntity2(taylorOrder, dimension);

	vector<Vector3D> 	position2 = physicalEntity2.getPosition();
	vector<Vector3D> 	orientation2 = physicalEntity2.getOrientation();

	checkEqual(physicalEntity2.getHandle(), defaultHandle);
	checkEqual(position2.size(), size);
	checkEqual(orientation2.size(), size);
	checkEqual(physicalEntity2.getDimension(), dimension);
	
}

TestCase( PhysicalEntityConstructorWithEntityAndParameters )
{
	int taylorOrder	= 5;
	int size		= taylorOrder + 1;
	int dimension	= 2;
	int handle		= 5;

	Entity entity(handle);

	// Constructor with non-default parameters and an Entity as parameter
	// Properties allocator not tested
	PhysicalEntity physicalEntity(taylorOrder, dimension, entity);

	vector<Vector3D> 	position 		= physicalEntity.getPosition();
	vector<Vector3D> 	orientation 	= physicalEntity.getOrientation();

	checkEqual( physicalEntity.getHandle() , handle );
	checkEqual( position.size() , size );
	checkEqual( orientation.size() , size );
	checkEqual( physicalEntity.getDimension() , dimension );

	vector<Vector3D> 			defaultPosition 	= physicalEntity.getPosition();
	vector<Vector3D> 			defaultOrientation 	= physicalEntity.getOrientation();
	
	checkEqual( physicalEntity.getHandle() , handle );
	checkEqual( defaultPosition.size() , size );
	checkEqual( defaultOrientation.size() , size );
	checkEqual( physicalEntity.getDimension() , dimension );
}

TestCase( SpacialSetFunctions )
{

	int taylorOrder	= 3;
	int dimension	= 3;
	int handle		= 0;
	PhysicalEntity physicalEntity(taylorOrder, dimension, handle);

	// setPosition(derivative, x, y, z)
	{
	double x = -5.4;
	double y = 8.3;
	double z = -1.7;
	int derivative = 0;

	Vector3D pos0(x , y , z);
	physicalEntity.setPosition(derivative, x, y, z);
	check( pos0==physicalEntity.getPosition(0) );
	}

	// setPosition(derivative, vector3D)
	{
	double x = -8.6;
	double y = 4.9;
	double z = -6.8;
	int derivative = 1;

	Vector3D pos0(x , y , z);
	physicalEntity.setPosition(derivative, pos0);
	check( pos0==physicalEntity.getPosition(derivative) );
	}

	// setPosition( vector<Vector3D> )
	{
	Vector3D pos0( 1.0 , -3.7 , -7.4 );
	Vector3D pos1( 6.2 , 1.9 , -2.8 );
	Vector3D pos2( 0.0 , 3.14 , 15.9);
	Vector3D pos3( -1.5 , 2.5 , 3.8);
	vector<Vector3D> posVec = { pos0, pos1, pos2, pos3 };

	physicalEntity.setPosition(posVec);

	check( pos0 == physicalEntity.getPosition()[0] );
	check( pos1 == physicalEntity.getPosition()[1] );
	check( pos2 == physicalEntity.getPosition()[2] );
	check( pos3 == physicalEntity.getPosition()[3] );
	}
}

TestCase( PropertiesTest )
{
	PhysicalEntity	physicalEntity;
	int taylorOrder	= 4;
	int size		= taylorOrder + 1;

	// setTaylorOrder
	physicalEntity.setTaylorOrder(taylorOrder);
	checkEqual( physicalEntity.getTaylorOrder() , taylorOrder );
	checkEqual( physicalEntity.getPosition().size() , size );

	// set and get properties
	double elasticModulus = 14.95;
	Property<double> elastic_modulus("ElasticModulus");

	physicalEntity.set(elastic_modulus, elasticModulus );
	checkEqual( physicalEntity.get(elastic_modulus) , elasticModulus );
	checkEqual(anyCast<double>(physicalEntity.getAsAnyValue(elastic_modulus.getName())),
		elasticModulus);
}

TestCase( ParticleConstructors )
{
	int taylorOrder = 4;
	int dimension = 3;
	int handle = 5;

	int defaultTaylorOrder = 3;
	int defaultDimension = 3;
	int defaultHandle = -1;

	PhysicalEntity base(taylorOrder, dimension, handle);

	Particle particle0;
	Particle particle1(taylorOrder, dimension, handle);
	Particle particle2(base);

	checkEqual(particle0.getHandle(), defaultHandle);
	checkEqual(particle0.getTaylorOrder(), defaultTaylorOrder);
	checkEqual(particle0.getDimension(), defaultDimension);

	checkEqual(particle1.getHandle(), handle);
	checkEqual(particle1.getTaylorOrder(), taylorOrder);
	checkEqual(particle1.getDimension(), dimension);
	

	checkEqual(particle2.getHandle(), handle);
	checkEqual(particle2.getTaylorOrder(), taylorOrder);
	checkEqual(particle2.getDimension(), dimension);
}

TestCase( ForcesAndTorques )
{
	Particle particle;

	checkEqual(particle.getBodyForce(), nullVector3D());
	checkEqual(particle.getContactForce(), nullVector3D());
	checkEqual(particle.getResultingForce(), nullVector3D());
	checkEqual(particle.getResultingTorque(), nullVector3D());
}

TestCase( SphericalParticleDistance )
{
	SphericalParticlePtr sph0( new SphericalParticle );
	SphericalParticlePtr sph1( new SphericalParticle );

	double x[2], y[2], z[2];

	x[0] = -3.7;
	y[0] = 4.9;
	z[0] = 5.31;
	sph0->setPosition( 0 , x[0] , y[0] , z[0] );

	x[1] = 3.5;
	y[1] = -6.9;
	z[1] = 0.17;
	sph1->setPosition( 0 , x[1] , y[1] , z[1] );

	double distance = 14.7478676424763;
	checkClose( sph0->distance(sph1) , distance , 1e-12 );
}

vector<Vector3D> pos(double t)
{
	vector<Vector3D> v;
	v.push_back( Vector3D(t, t+1, t+2) );
	v.push_back(Vector3D(t*t, 1, t/2));
	v.push_back(Vector3D(t*t*t, -1, t / 4));
	v.push_back(Vector3D(0, -t, -t*t));

	return v;
}
vector<Vector3D> ori(double t)
{
	vector<Vector3D> v;
	v.push_back(Vector3D(0, 1, 2));
	v.push_back(Vector3D(t*t, t*t*t, t-1));
	v.push_back(Vector3D(t*t - 6, t*t*(t-1), t + 1));
	v.push_back(Vector3D(1, 2*t, 3*t));

	return v;
}

TestCase(BoundaryTest)
{
	double t = 1.0;
	vector<Vector3D> myPosition = pos(t);
	vector<Vector3D> myOrientation = ori(t);

	Boundary boundary;
	boundary.setTaylorOrder(3);

	boundary.setPositionFunction(pos);
	boundary.setOrientationFunction(ori);

	boundary.updatePosition(t);
	boundary.updateOrientation(t);

	checkEqual(myPosition, boundary.getPosition());
	checkEqual(myOrientation, boundary.getOrientation());
}

TestCase(FixedInfinitePlaneTest)
{
	Vector3D origin1(1.0, 2.0, 3.0);
	Vector3D normalVector1(1.0, 1.0, 0.0);

	Vector3D origin2(-1.0, -1.0, -1.0);
	Vector3D vector1(5.0, 6.9, 7.8);
	Vector3D vector2(500, -9.5, 13.6);
	Vector3D vector3 = cross(vector1, vector2);
	double coefficient1 = 4.562;
	double coefficient2 = -560.82;

	FixedInfinitePlane plane1(origin1, normalVector1);
	checkEqual(plane1.getNormalVersor(), normalVector1.normalized());

	FixedInfinitePlane plane2 = FixedInfinitePlane::buildFromOriginAndTwoVectors(origin2, vector1, vector2);
	check(plane2.containsVector(vector1));
	check(plane2.containsVector(vector2));
	check(plane2.containsVector(coefficient1*vector1 + coefficient2*vector2));

	FixedInfinitePlane plane3 = FixedInfinitePlane::buildFromThreePoints(origin2, vector1 + origin2, vector2 + origin2);
	check( plane2 == plane3 );
}