#include "PhysicalEntity.h"

// ------------------------------- Constructor -------------------------------
PhysicalEntity::PhysicalEntity()
{
	reservePropertyMemory();
	reservePositionOrientationMemory();
}

PhysicalEntity::PhysicalEntity(const int taylorOrder, const int dimension)
	: Entity()
{
	// Set order and dimension
	this->taylorOrder = taylorOrder;
	this->dimension = dimension;

	// Alloc memory to properties
	reservePositionOrientationMemory();

	// Alloc memory to vectors position and orientation
	reservePositionOrientationMemory();
}

PhysicalEntity::PhysicalEntity(const int handle, const vector<double> scalarPropertyVector)
	: Entity(handle)
{
	// Alloc memory to vectors position and orientation
	reservePositionOrientationMemory();

	// Set scalarProperty vector as the input vector
	setScalarProperty(scalarPropertyVector);
}

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

void PhysicalEntity::reservePositionOrientationMemory()
{
	int size = taylorOrder + 1;
	this->position.reserve(size);
	this->orientation.reserve(size);
	
	for( int i=0 ; i<size ; i++){
		this->position[i].reserve(dimension);
		this->orientation[i].reserve(dimension);
	}
}

void PhysicalEntity::reservePropertyMemory()
{
	scalarProperty.reserve(N_SCALAR_PROPERTY);
	
	// vectorialProperty: vectors dimension x 1
	vectorialProperty.reserve(N_VECTORIAL_PROPERTY);
	for(int i=0 ; i<N_VECTORIAL_PROPERTY ; i++){
		vectorialProperty[i].reserve(dimension);
	}
	
	// matricialProperty: matrices dimension x dimension
	matricialProperty.reserve(N_MATRICIAL_PROPERTY);
	for(int i=0 ; i<N_VECTORIAL_PROPERTY ; i++){
		matricialProperty[i].reserve(dimension);
		for(int j=0 ; j<dimension ; j++){
			matricialProperty[i][j].reserve(dimension);
		}
	}

}