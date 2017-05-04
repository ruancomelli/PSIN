#define BOOST_TEST_MODULE EntityLibTest

// UtilsLib
// #include <Mathematics.hpp>
#include <Vector3D.hpp>
#include <Vector.hpp>
#include <Test.hpp>
// #include <Foreach.hpp>

// EntityLib
// #include <Boundary.hpp>
// #include <FixedInfinitePlane.hpp>

#include <HandledEntity.hpp>
#include <SpatialEntity.hpp>
#include <SocialEntity.hpp>
// #include <PhysicalEntity.hpp>
// #include <Particle.hpp>
// #include <SphericalParticle.hpp>

// IOLib
// #include <vectorIO.hpp>

// PropertyLib
// #include <ValuedPropertyContainer.hpp>

using namespace std;



TestCase( HandledEntityTest )
{
	HandledEntity entity1;

	// Test the default handle and the getHandle function
	int defaultHandle = DEFAULT_HANDLED_ENTITY_HANDLE;
	checkEqual( entity1.getHandle() , defaultHandle );

	// Test the setHandle function
	int handleToSet = 2;
	entity1.setHandle(handleToSet);
	checkEqual( entity1.getHandle() , handleToSet );

	// Test constructor passing one argument
	int initialHandle = 1;
	HandledEntity entity2(initialHandle);

	checkEqual( entity2.getHandle() , initialHandle );

	HandledEntity entity3 = entity1;

	checkEqual( entity1.getHandle(), entity3.getHandle() );

	int commonHandle = 7;
	HandledEntity entity4(commonHandle);
	HandledEntity entity5(commonHandle);

	check(entity4 == entity5);
}

TestCase( SocialEntityBaseClassTest )
{
	int defaultHandle = -1;
	int handleToSet = 3;

	SocialEntity social1;

	checkEqual(social1.getHandle(), defaultHandle);

	social1.setHandle(handleToSet);

	checkEqual(social1.getHandle(), handleToSet);

	SocialEntity social2(handleToSet);

	checkEqual(social2.getHandle(), handleToSet);
}

TestCase(SocialEntityNeighborhoodTest)
{
	int handle1 = 3;
	int handle2 = 10;

	SocialEntity social;

	check(social.getNeighborhood().empty());

	SocialEntity neighbor1(handle1);
	SocialEntity neighbor2(handle2);

	social.addNeighbor(neighbor1);
	social.addNeighbor(neighbor2);

	check(social.getNeighborhood().count(handle1));
	check(social.getNeighborhood().count(handle2));

	social.removeNeighbor(neighbor2);

	check(social.getNeighborhood().count(handle1));
	check(!social.getNeighborhood().count(handle2));
}

TestCase(SpatialEntityTaylorOrderTest)
{
	int validTaylorOrder = 4;
	int validTaylorOrder2 = 5;
	int invalidTaylorOrder = -1;

	SpatialEntity spatial(validTaylorOrder);
	checkEqual(spatial.getTaylorOrder(), validTaylorOrder);

	// Uncomment the following line to get runtime errors:
	// SpatialEntity invalidSpatial(invalidTaylorOrder);

	spatial.setTaylorOrder(validTaylorOrder2);
	checkEqual(spatial.getTaylorOrder(), validTaylorOrder2);

	// Uncomment the following line to get runtime errors:
	// spatial.setTaylorOrder(invalidTaylorOrder);

	SpatialEntity spatial3;
	checkEqual(spatial3.getTaylorOrder(), DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
}

std::ostream & operator << (std::ostream & stream, const Vector3D & v){
	stream << v.x() << "    " << v.y() << "    " << v.z() << std::endl;
	return stream;
}

template <class type> 
std::ostream & operator<<( std::ostream & outputFile , const std::vector<type> & v){
	for( type entry : v )
	{
		outputFile << entry << std::endl;
	}

	return outputFile;
}

TestCase(SpatialEntityPositionMatrixOrientationMatrixTest)
{
	std::vector<Vector3D> positionMatrix;
	positionMatrix.push_back( Vector3D(1.8, 2.5, 3.9) );
	positionMatrix.push_back( Vector3D(8.6, 7.4, 2.1) );
	positionMatrix.push_back( Vector3D(-1.2, 0.0, 300.5) );
	positionMatrix.push_back( Vector3D(-9.9, 0.31, 0.0021) );
	positionMatrix.push_back( Vector3D(8.9, -1111.0, 3.9) );

	std::vector<Vector3D> orientationMatrix;
	orientationMatrix.push_back( Vector3D(5.8, -4.65, -0.12) );
	orientationMatrix.push_back( Vector3D(86.9, 61.45, -10.89) );
	orientationMatrix.push_back( Vector3D(1.89, -65.0, 0.0) );
	orientationMatrix.push_back( Vector3D(0.0, 18.5, 11.54) );
	orientationMatrix.push_back( Vector3D(-89.56, 112.0, 123456789.0) );

	SpatialEntity spatial( positionMatrix.size() - 1 );
	spatial.setPositionMatrix(positionMatrix);
	spatial.setOrientationMatrix(orientationMatrix);

	checkEqual(spatial.getPositionMatrix(), positionMatrix);
	checkEqual(spatial.getOrientationMatrix(), orientationMatrix);

	// Uncomment the following lines to get runtime errors:
	// orientationMatrix.push_back( Vector3D(-0.5, 12.13, 89.78) );
	// spatial.setOrientationMatrix(orientationMatrix);
}

TestCase(SpatialEntityPositionVelocityAccelerationTest)
{
	int validDerivative = 3;
	int invalidDerivative = -1;

	SpatialEntity spatial;

	Vector3D position1(1.5, 1.6, 1.7);
	Vector3D position2(-0.5, 1.55, 30.65);
	Vector3D position3(3.14159, 1.55, 0.0);

	spatial.setPosition(position1);
	checkEqual(spatial.getPosition(), position1);

	spatial.setPosition(position2.x(), position2.y(), position2.z());
	checkEqual(spatial.getPosition(), position2);

	spatial.setPosition(position3.x(), position3.y());
	checkEqual(spatial.getPosition(), position3);

	Vector3D velocity1(8.9, 11.5, 36.5);
	Vector3D velocity2(7.1, 131.7, 0.58);
	Vector3D velocity3(-11.25, 0.56, 0.0);

	spatial.setVelocity(velocity1);
	checkEqual(spatial.getVelocity(), velocity1);

	spatial.setVelocity(velocity2.x(), velocity2.y(), velocity2.z());
	checkEqual(spatial.getVelocity(), velocity2);

	spatial.setVelocity(velocity3.x(), velocity3.y());
	checkEqual(spatial.getVelocity(), velocity3);

	Vector3D acceleration1(18.07, -3.141598, 1.618);
	Vector3D acceleration2(1.2351, -485.6, 12.5);
	Vector3D acceleration3(88.97, 15.65, 0.0);

	spatial.setAcceleration(acceleration1);
	checkEqual(spatial.getAcceleration(), acceleration1);

	spatial.setAcceleration(acceleration2.x(), acceleration2.y(), acceleration2.z());
	checkEqual(spatial.getAcceleration(), acceleration2);

	spatial.setAcceleration(acceleration3.x(), acceleration3.y());
	checkEqual(spatial.getAcceleration(), acceleration3);

	Vector3D derivative1(2.98, 9.87, -8251.02);
	Vector3D derivative2(0.0, -68.1, 48.8);
	Vector3D derivative3(-64.5, 112358.1321, 0.0);

	spatial.setPositionDerivative(validDerivative, derivative1);
	checkEqual(spatial.getPositionDerivative(validDerivative), derivative1);

	spatial.setPositionDerivative(validDerivative, derivative2.x(), derivative2.y(), derivative2.z());
	checkEqual(spatial.getPositionDerivative(validDerivative), derivative2);

	spatial.setPositionDerivative(validDerivative, derivative3.x(), derivative3.y());
	checkEqual(spatial.getPositionDerivative(validDerivative), derivative3);

	// Uncomment the following lines to get runtime errors:
	// spatial.setPositionDerivative(invalidDerivative, derivative1);
	// spatial.getPositionDerivative(invalidDerivative);
}

TestCase(SpatialEntityAngularPositionVelocityAccelerationTest)
{
	int validDerivative = 3;
	int invalidDerivative = -1;

	SpatialEntity spatial;

	Vector3D orientation1(1.5, 1.6, 1.7);
	Vector3D orientation2(-0.5, 1.55, 30.65);
	Vector3D orientation3(3.14159, 1.55, 0.0);

	spatial.setOrientation(orientation1);
	checkEqual(spatial.getOrientation(), orientation1);

	spatial.setOrientation(orientation2.x(), orientation2.y(), orientation2.z());
	checkEqual(spatial.getOrientation(), orientation2);

	spatial.setOrientation(orientation3.x(), orientation3.y());
	checkEqual(spatial.getOrientation(), orientation3);

	Vector3D angularVelocity1(8.9, 11.5, 36.5);
	Vector3D angularVelocity2(7.1, 131.7, 0.58);
	Vector3D angularVelocity3(-11.25, 0.56, 0.0);

	spatial.setAngularVelocity(angularVelocity1);
	checkEqual(spatial.getAngularVelocity(), angularVelocity1);

	spatial.setAngularVelocity(angularVelocity2.x(), angularVelocity2.y(), angularVelocity2.z());
	checkEqual(spatial.getAngularVelocity(), angularVelocity2);

	spatial.setAngularVelocity(angularVelocity3.x(), angularVelocity3.y());
	checkEqual(spatial.getAngularVelocity(), angularVelocity3);

	Vector3D angularAcceleration1(18.07, -3.141598, 1.618);
	Vector3D angularAcceleration2(1.2351, -485.6, 12.5);
	Vector3D angularAcceleration3(88.97, 15.65, 0.0);

	spatial.setAngularAcceleration(angularAcceleration1);
	checkEqual(spatial.getAngularAcceleration(), angularAcceleration1);

	spatial.setAngularAcceleration(angularAcceleration2.x(), angularAcceleration2.y(), angularAcceleration2.z());
	checkEqual(spatial.getAngularAcceleration(), angularAcceleration2);

	spatial.setAngularAcceleration(angularAcceleration3.x(), angularAcceleration3.y());
	checkEqual(spatial.getAngularAcceleration(), angularAcceleration3);

	Vector3D derivative1(2.98, 9.87, -8251.02);
	Vector3D derivative2(0.0, -68.1, 48.8);
	Vector3D derivative3(-64.5, 112358.1321, 0.0);

	spatial.setOrientationDerivative(validDerivative, derivative1);
	checkEqual(spatial.getOrientationDerivative(validDerivative), derivative1);

	spatial.setOrientationDerivative(validDerivative, derivative2.x(), derivative2.y(), derivative2.z());
	checkEqual(spatial.getOrientationDerivative(validDerivative), derivative2);

	spatial.setOrientationDerivative(validDerivative, derivative3.x(), derivative3.y());
	checkEqual(spatial.getOrientationDerivative(validDerivative), derivative3);

	// Uncomment the following lines to get runtime errors:
	// spatial.setOrientationDerivative(invalidDerivative, derivative1);
	// spatial.getOrientationDerivative(invalidDerivative);
}

// TestCase( PhysicalEntityDefaultConstructor )
// {
// 	// Default Constructor
// 	PhysicalEntity 		physicalEntity;
// 	int 				defaultTaylorOrder 	= 3;
// 	int 				defaultSize 		= defaultTaylorOrder + 1;
// 	int 				defaultDimension 	= 3;
// 	int					defaultHandle		= -1;
// 	GeometryType geometryType = DEFAULT;

// 	vector<Vector3D> 			defaultPosition 	= physicalEntity.getPosition();
// 	vector<Vector3D> 			defaultOrientation 	= physicalEntity.getOrientation();
	
// 	checkEqual( physicalEntity.getHandle() , defaultHandle );
// 	checkEqual( defaultPosition.size() , defaultSize );
// 	checkEqual( defaultOrientation.size() , defaultSize );
// 	checkEqual( physicalEntity.getDimension() , defaultDimension );
// 	checkEqual( physicalEntity.getGeometry(), geometryType );
// }

// TestCase( PhysicalEntityConstructorWithEntity )
// {
// 	int 				defaultTaylorOrder 	= 3;
// 	int 				defaultSize 		= defaultTaylorOrder + 1;
// 	int 				defaultDimension 	= 3;
// 	int					handle				= 5;
// 	GeometryType geometryType = DEFAULT;

// 	Entity				entity(handle);
	
// 	PhysicalEntity 		physicalEntity(entity);

// 	vector<Vector3D> 			defaultPosition 	= physicalEntity.getPosition();
// 	vector<Vector3D> 			defaultOrientation 	= physicalEntity.getOrientation();
	
// 	checkEqual( physicalEntity.getHandle() , handle );
// 	checkEqual( defaultPosition.size() , defaultSize );
// 	checkEqual( defaultOrientation.size() , defaultSize );
// 	checkEqual( physicalEntity.getDimension() , defaultDimension );
// 	checkEqual(physicalEntity.getGeometry(), geometryType);
// }

// TestCase( PhysicalEntityConstructorWithParameters )
// {
// 	int taylorOrder	= 3;
// 	int size		= taylorOrder + 1;
// 	int dimension	= 2;
// 	int handle		= 5;

// 	// Constructor with non-default parameters
// 	// Properties allocator not tested
// 	PhysicalEntity physicalEntity(taylorOrder, dimension, handle);

// 	vector<Vector3D> 	position 		= physicalEntity.getPosition();
// 	vector<Vector3D> 	orientation 	= physicalEntity.getOrientation();

// 	checkEqual( physicalEntity.getHandle() , handle );
// 	checkEqual( position.size() , size );
// 	checkEqual( orientation.size() , size );
// 	checkEqual( physicalEntity.getDimension() , dimension );

// 	// Constructor with non-default parameters, but without handle
// 	int defaultHandle = -1;
// 	PhysicalEntity physicalEntity2(taylorOrder, dimension);

// 	vector<Vector3D> 	position2 = physicalEntity2.getPosition();
// 	vector<Vector3D> 	orientation2 = physicalEntity2.getOrientation();

// 	checkEqual(physicalEntity2.getHandle(), defaultHandle);
// 	checkEqual(position2.size(), size);
// 	checkEqual(orientation2.size(), size);
// 	checkEqual(physicalEntity2.getDimension(), dimension);
	
// }

// TestCase( PhysicalEntityConstructorWithEntityAndParameters )
// {
// 	int taylorOrder	= 5;
// 	int size		= taylorOrder + 1;
// 	int dimension	= 2;
// 	int handle		= 5;

// 	Entity entity(handle);

// 	// Constructor with non-default parameters and an Entity as parameter
// 	// Properties allocator not tested
// 	PhysicalEntity physicalEntity(taylorOrder, dimension, entity);

// 	vector<Vector3D> 	position 		= physicalEntity.getPosition();
// 	vector<Vector3D> 	orientation 	= physicalEntity.getOrientation();

// 	checkEqual( physicalEntity.getHandle() , handle );
// 	checkEqual( position.size() , size );
// 	checkEqual( orientation.size() , size );
// 	checkEqual( physicalEntity.getDimension() , dimension );

// 	vector<Vector3D> 			defaultPosition 	= physicalEntity.getPosition();
// 	vector<Vector3D> 			defaultOrientation 	= physicalEntity.getOrientation();
	
// 	checkEqual( physicalEntity.getHandle() , handle );
// 	checkEqual( defaultPosition.size() , size );
// 	checkEqual( defaultOrientation.size() , size );
// 	checkEqual( physicalEntity.getDimension() , dimension );
// }

// TestCase( SpacialSetFunctions )
// {

// 	int taylorOrder	= 3;
// 	int dimension	= 3;
// 	int handle		= 0;
// 	PhysicalEntity physicalEntity(taylorOrder, dimension, handle);

// 	// setPosition(derivative, x, y, z)
// 	{
// 	double x = -5.4;
// 	double y = 8.3;
// 	double z = -1.7;
// 	int derivative = 0;

// 	Vector3D pos0(x , y , z);
// 	physicalEntity.setPosition(derivative, x, y, z);
// 	check( pos0==physicalEntity.getPosition(0) );
// 	}

// 	// setPosition(derivative, vector3D)
// 	{
// 	double x = -8.6;
// 	double y = 4.9;
// 	double z = -6.8;
// 	int derivative = 1;

// 	Vector3D pos0(x , y , z);
// 	physicalEntity.setPosition(derivative, pos0);
// 	check( pos0==physicalEntity.getPosition(derivative) );
// 	}

// 	// setPosition( vector<Vector3D> )
// 	{
// 	Vector3D pos0( 1.0 , -3.7 , -7.4 );
// 	Vector3D pos1( 6.2 , 1.9 , -2.8 );
// 	Vector3D pos2( 0.0 , 3.14 , 15.9);
// 	Vector3D pos3( -1.5 , 2.5 , 3.8);
// 	vector<Vector3D> posVec = { pos0, pos1, pos2, pos3 };

// 	physicalEntity.setPosition(posVec);

// 	check( pos0 == physicalEntity.getPosition()[0] );
// 	check( pos1 == physicalEntity.getPosition()[1] );
// 	check( pos2 == physicalEntity.getPosition()[2] );
// 	check( pos3 == physicalEntity.getPosition()[3] );
// 	}
// }

// TestCase( PropertiesTest )
// {
// 	PhysicalEntity	physicalEntity;
// 	int taylorOrder	= 4;
// 	int size		= taylorOrder + 1;

// 	// setTaylorOrder
// 	physicalEntity.setTaylorOrder(taylorOrder);
// 	checkEqual( physicalEntity.getTaylorOrder() , taylorOrder );
// 	checkEqual( physicalEntity.getPosition().size() , size );

// 	// set and get properties
// 	double elasticModulus = 14.95;
// 	Property<double> elastic_modulus("ElasticModulus");

// 	physicalEntity.set(elastic_modulus, elasticModulus );
// 	checkEqual( physicalEntity.get(elastic_modulus) , elasticModulus );
// 	checkEqual(anyCast<double>(physicalEntity.getAsAnyValue(elastic_modulus.getName())),
// 		elasticModulus);
// }

// TestCase( ParticleConstructors )
// {
// 	int taylorOrder = 4;
// 	int dimension = 3;
// 	int handle = 5;

// 	int defaultTaylorOrder = 3;
// 	int defaultDimension = 3;
// 	int defaultHandle = -1;

// 	PhysicalEntity base(taylorOrder, dimension, handle);

// 	Particle particle0;
// 	Particle particle1(taylorOrder, dimension, handle);
// 	Particle particle2(base);

// 	checkEqual(particle0.getHandle(), defaultHandle);
// 	checkEqual(particle0.getTaylorOrder(), defaultTaylorOrder);
// 	checkEqual(particle0.getDimension(), defaultDimension);

// 	checkEqual(particle1.getHandle(), handle);
// 	checkEqual(particle1.getTaylorOrder(), taylorOrder);
// 	checkEqual(particle1.getDimension(), dimension);
	

// 	checkEqual(particle2.getHandle(), handle);
// 	checkEqual(particle2.getTaylorOrder(), taylorOrder);
// 	checkEqual(particle2.getDimension(), dimension);
// }

// TestCase( ForcesAndTorques )
// {
// 	Particle particle;

// 	checkEqual(particle.getBodyForce(), nullVector3D());
// 	checkEqual(particle.getContactForce(), nullVector3D());
// 	checkEqual(particle.getResultingForce(), nullVector3D());
// 	checkEqual(particle.getResultingTorque(), nullVector3D());
// }

// TestCase( SphericalParticleDistance )
// {
// 	SphericalParticlePtr sph0( new SphericalParticle );
// 	SphericalParticlePtr sph1( new SphericalParticle );

// 	double x[2], y[2], z[2];

// 	x[0] = -3.7;
// 	y[0] = 4.9;
// 	z[0] = 5.31;
// 	sph0->setPosition( 0 , x[0] , y[0] , z[0] );

// 	x[1] = 3.5;
// 	y[1] = -6.9;
// 	z[1] = 0.17;
// 	sph1->setPosition( 0 , x[1] , y[1] , z[1] );

// 	double distance = 14.7478676424763;
// 	checkClose( sph0->distance(sph1) , distance , 1e-12 );
// }

// vector<Vector3D> pos(double t)
// {
// 	vector<Vector3D> v;
// 	v.push_back( Vector3D(t, t+1, t+2) );
// 	v.push_back(Vector3D(t*t, 1, t/2));
// 	v.push_back(Vector3D(t*t*t, -1, t / 4));
// 	v.push_back(Vector3D(0, -t, -t*t));

// 	return v;
// }
// vector<Vector3D> ori(double t)
// {
// 	vector<Vector3D> v;
// 	v.push_back(Vector3D(0, 1, 2));
// 	v.push_back(Vector3D(t*t, t*t*t, t-1));
// 	v.push_back(Vector3D(t*t - 6, t*t*(t-1), t + 1));
// 	v.push_back(Vector3D(1, 2*t, 3*t));

// 	return v;
// }

// TestCase(BoundaryTest)
// {
// 	double t = 1.0;
// 	vector<Vector3D> myPosition = pos(t);
// 	vector<Vector3D> myOrientation = ori(t);

// 	Boundary boundary;
// 	boundary.setTaylorOrder(3);

// 	boundary.setPositionFunction(pos);
// 	boundary.setOrientationFunction(ori);

// 	boundary.updatePosition(t);
// 	boundary.updateOrientation(t);

// 	checkEqual(myPosition, boundary.getPosition());
// 	checkEqual(myOrientation, boundary.getOrientation());
// }

// TestCase(FixedInfinitePlaneTest)
// {
// 	Vector3D origin1(1.0, 2.0, 3.0);
// 	Vector3D normalVector1(1.0, 1.0, 0.0);

// 	Vector3D origin2(-1.0, -1.0, -1.0);
// 	Vector3D vector1(5.0, 6.9, 7.8);
// 	Vector3D vector2(500, -9.5, 13.6);
// 	Vector3D vector3 = cross(vector1, vector2);
// 	double coefficient1 = 4.562;
// 	double coefficient2 = -560.82;

// 	FixedInfinitePlane plane1(origin1, normalVector1);
// 	checkEqual(plane1.getNormalVersor(), normalVector1.normalized());

// 	FixedInfinitePlane plane2 = FixedInfinitePlane::buildFromOriginAndTwoVectors(origin2, vector1, vector2);
// 	check(plane2.containsVector(vector1));
// 	check(plane2.containsVector(vector2));
// 	check(plane2.containsVector(coefficient1*vector1 + coefficient2*vector2));

// 	FixedInfinitePlane plane3 = FixedInfinitePlane::buildFromThreePoints(origin2, vector1 + origin2, vector2 + origin2);
// 	check( plane2 == plane3 );
// }