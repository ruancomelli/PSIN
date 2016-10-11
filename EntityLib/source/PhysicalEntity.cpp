#include <PhysicalEntity.h>

// ------------------------------- Constructor -------------------------------
PhysicalEntity::PhysicalEntity()  : Entity(), taylorOrder(2), dimension(3), geometry(DEFAULT)
{
	// Initialize Properties
	reservePropertyMemory();
	// Initialize Position and Orientation
	reservePositionOrientationMemory();
}

PhysicalEntity::PhysicalEntity(const int taylorOrder, const int dimension, const int handle)
	: Entity(handle), geometry(DEFAULT)
{
	// Set order and dimension
	this->taylorOrder = taylorOrder;
	this->dimension = dimension;

	// Alloc memory to properties
	reservePositionOrientationMemory();

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

double PhysicalEntity::getScalarProperty(const int scalarPropertyIdentifier)
{
	return this->scalarProperty[scalarPropertyIdentifier];
}

DoubleVector PhysicalEntity::getScalarProperty()
{
	return this->scalarProperty;
}

//------------------------------- Position -------------------------------
void PhysicalEntity::setPosition(const DoubleVector position, const int derivative)
{
	this->position[derivative] = position;
}

void PhysicalEntity::setPosition(const DoubleVector2D position)
{
	this->position = position;
	
	return;
}

DoubleVector2D PhysicalEntity::getPosition() const
{
	return this->position;
}

DoubleVector PhysicalEntity::getPosition(const int derivate) const
{
	return this->position[derivate];
}

// ------------------------------- Orientation -------------------------------
void PhysicalEntity::setOrientation(const DoubleVector2D orientation)
{
	this->orientation = orientation;
	
	return;
}

DoubleVector2D PhysicalEntity::getOrientation(void) const
{
	return this->orientation;
}

DoubleVector PhysicalEntity::getOrientation(const int derivate) const
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

void PhysicalEntity::reservePositionOrientationMemory(void)
{
	int size = taylorOrder + 1;
	this->position.resize(size);
	this->orientation.resize(size);
	
	for( int i=0 ; i<size ; i++){
		this->position[i].resize(dimension);
		this->orientation[i].resize(dimension);
	}
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