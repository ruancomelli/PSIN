#include <PhysicalEntity.h>

// ------------------------------- Constructor -------------------------------
PhysicalEntity::PhysicalEntity()
	: Entity(), geometry(DEFAULT)
{
	setTaylorOrder(2);
	setDimension(3);
	// Initialize Properties
	reservePropertyMemory();
	// Initialize Position and Orientation
	reservePositionOrientationMemory();
}

PhysicalEntity::PhysicalEntity(const int taylorOrder, const int dimension, const int handle)
	: Entity(handle), geometry(DEFAULT)
{
	// Set order and dimension
	setTaylorOrder(taylorOrder);
	setDimension(dimension);

	// Alloc memory to properties
	reservePropertyMemory();

	// Alloc memory to vectors position and orientation
	reservePositionOrientationMemory();
}
/*
PhysicalEntity::PhysicalEntity(const int handle, const vector<double> scalarPropertyVector)
	: Entity(handle)
{
	// Alloc memory to vectors position and orientation
	reservePositionOrientationMemory();

	// Set scalarProperty vector as the input vector
	setScalarProperty(scalarPropertyVector);
}*/

// ------------------------------- Property -------------------------------

void PhysicalEntity::setScalarProperty(const int scalarPropertyIdentifier, const double scalarPropertyValue)
{
	this->scalarProperty[scalarPropertyIdentifier] = scalarPropertyValue;
}

void PhysicalEntity::setScalarProperty(const DoubleVector scalarPropertyVector)
{
	this->scalarProperty = scalarPropertyVector;
}

double PhysicalEntity::getScalarProperty(const int scalarPropertyIdentifier) const
{
	return this->scalarProperty[scalarPropertyIdentifier];
}

DoubleVector PhysicalEntity::getScalarProperty() const
{
	return this->scalarProperty;
}

//------------------------------- Position -------------------------------

void PhysicalEntity::setPosition(const int derivative, const double x, const double y, const double z)
{
	this->position[derivative].x() = x;
	this->position[derivative].y() = y;
	this->position[derivative].z() = z;
}

void PhysicalEntity::setPosition(const int derivative, const Vector3D & vec)
{
	this->position[derivative] = vec;
}

void PhysicalEntity::setPosition(const vector<Vector3D> & position)
{
	if( position.size() != (this->taylorOrder + 1) )
	{
		//ERROR!
	}
	this->position = position;
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
	this->orientation[derivative].x() = x;
	this->orientation[derivative].y() = y;
	this->orientation[derivative].z() = z;
}

void PhysicalEntity::setOrientation(const int derivative, const Vector3D & vec)
{
	this->orientation[derivative] = vec;
}

void PhysicalEntity::setOrientation(const vector<Vector3D> & orientation)
{
	if( orientation.size() != (this->taylorOrder + 1) )
	{
		//ERROR!
	}
	this->orientation = orientation;
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

// ------------------------------- Distance and Touching -------------------------------
double PhysicalEntity::distance(const PhysicalEntity physicalEntity){
	Vector3D difference = this->position[0] - physicalEntity.position[0];
	return difference.length();
}

// ------------------------------- Auxiliar Functions -------------------------------

void PhysicalEntity::reservePositionOrientationMemory(void)
{
	int size = taylorOrder + 1;
	this->position.resize(size);
	this->orientation.resize(size);
}

void PhysicalEntity::reservePropertyMemory(void)
{
	// scalarProperty: 1 x 1
	scalarProperty.resize(N_SCALAR_PROPERTY);
	
	// vectorialProperty: vectors dimension x 1
	vectorialProperty.resize(N_VECTORIAL_PROPERTY);
	for(int i=0 ; i<N_VECTORIAL_PROPERTY ; i++){
		vectorialProperty[i].resize(dimension);
	}
	
	// matricialProperty: matrices dimension x dimension
	matricialProperty.resize(N_MATRICIAL_PROPERTY);
	for(int i=0 ; i<N_VECTORIAL_PROPERTY ; i++){
		matricialProperty[i].resize(dimension);
		for(int j=0 ; j<dimension ; j++){
			matricialProperty[i][j].resize(dimension);
		}
	}
}

void PhysicalEntity::setTaylorOrder(const int taylorOrder)
{
	if(taylorOrder < 0)
	{
		throw runtime_error("Invalid taylorOrder inserted. taylorOrder must be nonnegative.");
	}
	else
	{
		this->taylorOrder = taylorOrder;
	}
}

void PhysicalEntity::setDimension(const int dimension)
{
	if( (dimension != 2) && (dimension != 3))
	{
		throw runtime_error("Invalid dimension value inserted. dimension must be 2 or 3.");
	}
	else
	{
		this->taylorOrder = taylorOrder;
	}
}
