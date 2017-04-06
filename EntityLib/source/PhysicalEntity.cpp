#include <PhysicalEntity.hpp>

// Standard
#include <stdexcept>

// PropertyLib
#include <PropertyDefinitions.hpp>

using std::string;
using std::vector;

// ------------------------------- Constructors -------------------------------
int PhysicalEntity::dimension = 3;

PhysicalEntity::PhysicalEntity()
	: Entity(), 
	geometry(DEFAULT)
{
	setTaylorOrder(3); // It calls resizePositionOrientation
	setDimension(3);

	set( PropertyDefinitions::mass, 1 );
	set( PropertyDefinitions::moment_of_inertia , 1 );
}

PhysicalEntity::PhysicalEntity( const Entity & base )
	: Entity(base), geometry(DEFAULT)
{
	setTaylorOrder(3);
	setDimension(3);

	set(PropertyDefinitions::mass, 1 );
	set(PropertyDefinitions::moment_of_inertia, 1 );
}

PhysicalEntity::PhysicalEntity(const int taylorOrder, const int dim, const int handle)
	: Entity(handle), geometry(DEFAULT)
{
	// Set order and dimension
	setTaylorOrder(taylorOrder);
	setDimension(dim);

	set(PropertyDefinitions::mass, 1 );
	set(PropertyDefinitions::moment_of_inertia , 1 );
}

PhysicalEntity::PhysicalEntity(const int taylorOrder, const int dim,  const Entity & base)
	: Entity(base), geometry(DEFAULT)
{
	setTaylorOrder(taylorOrder);
	setDimension(dim);
	
	set(PropertyDefinitions::mass, 1 );
	set(PropertyDefinitions::moment_of_inertia , 1 );
}
// ------------------------------- Property -------------------------------

void PhysicalEntity::requireProperties( const RawPropertyContainer & raw )
{
	this->propertyContainer = PropertyContainer(raw);
}

	// dimension
int PhysicalEntity::getDimension(void) const
{
	return this->dimension;
}

	// taylorOrder
void PhysicalEntity::setTaylorOrder(const int taylorOrder)
{
	if(taylorOrder < 3 || taylorOrder > 5)
	{
		throw std::runtime_error("Invalid taylorOrder inserted. taylorOrder must be either 3, 4 or 5.");
	}
	else
	{
		this->taylorOrder = taylorOrder;
		resizePositionOrientation();
	}
}

int PhysicalEntity::getTaylorOrder(void) const
{
	return this->taylorOrder;
}

SharedPointer<std::set<string>> PhysicalEntity::getPropertyNames( void ) const
{
	return this->propertyContainer.getPropertyNames();
}

void PhysicalEntity::set( const string & rawName, const Any & value )
{
	this->propertyContainer.setProperty( rawName, value );
}

Any PhysicalEntity::getAsAnyValue( const string & name ) const
{
	return this->propertyContainer.getValue(name);
}
//------------------------------- Position -------------------------------

void PhysicalEntity::setPosition(const int derivative, const double x, const double y, const double z)
{
	setSpatial(this->position, derivative, x, y, z);
}

void PhysicalEntity::setPosition(const int derivative, const Vector3D & vec)
{
	setSpatial(this->position, derivative, vec);
}

void PhysicalEntity::setPosition(const vector<Vector3D> & position)
{
	setSpatial(this->position, position);
}

vector<Vector3D> PhysicalEntity::getPosition() const
{
	return this->position;
}

Vector3D PhysicalEntity::getPosition(const int derivate) const
{
	return this->position[derivate];
}

// ------------------------------- Orientation -------------------------------
void PhysicalEntity::setOrientation(const int derivative, const double x, const double y, const double z)
{
	setSpatial(this->orientation, derivative, x, y, z);
}

void PhysicalEntity::setOrientation(const int derivative, const Vector3D & vec)
{
	setSpatial(this->orientation, derivative, vec);
}

void PhysicalEntity::setOrientation(const vector<Vector3D> & orientation)
{
	setSpatial(this->orientation, orientation);
}

vector<Vector3D> PhysicalEntity::getOrientation(void) const
{
	return this->orientation;
}

Vector3D PhysicalEntity::getOrientation(const int derivate) const
{
	return this->orientation[derivate];
}

// ------------------------------- Geometry -------------------------------
void PhysicalEntity::setGeometry(const GeometryType geometry)
{
	this->geometry = geometry;
	
	return;
}

GeometryType PhysicalEntity::getGeometry() const
{
	return this->geometry;
}

// ------------------------------- Auxiliar Functions -------------------------------

void PhysicalEntity::resizePositionOrientation(void)
{
	int size = taylorOrder + 1;
	this->position.resize(size);
	this->orientation.resize(size);
}

void PhysicalEntity::setDimension(const int dim)
{
	if( (dim != 2) && (dim != 3))
	{
		throw std::runtime_error("Invalid dimension value inserted. Dimension must be either 2 or 3.");
	}
	else
	{
		dimension = dim;
	}
}

	// set spacial positions
void PhysicalEntity::setSpatial(vector<Vector3D> & spatial, const int derivative, const double x, const double y, const double z)
{
	spatial[derivative].x() = x;
	spatial[derivative].y() = y;
	spatial[derivative].z() = z;
}

void PhysicalEntity::setSpatial(vector<Vector3D> & spatial, const int derivative, const Vector3D & vec)
{
	spatial[derivative] = vec;
}

void PhysicalEntity::setSpatial(vector<Vector3D> & spatialToSet, const vector<Vector3D> & spatial)
{
	if( spatial.size() != (this->taylorOrder + 1) )
	{
		throw std::runtime_error("taylorOrder does not match spatial's size in function PhysicalEntity::setSpatial(vector<Vector3D> & spatialToSet, const vector<Vector3D> & spatial)");
	}
	spatialToSet = spatial;
}
