#include <PhysicalEntity.h>

// ------------------------------- Constructor -------------------------------
int PhysicalEntity::dimension = 3;

PhysicalEntity::PhysicalEntity()
	: Entity(), geometry(DEFAULT)
{
	setTaylorOrder(3); // It calls reservePositionOrientationMemory
	setDimension(3);
	// Initialize Properties
	reservePropertyMemory();
}

PhysicalEntity::PhysicalEntity(const int taylorOrder, const int dim, const int handle)
	: Entity(handle), geometry(DEFAULT)
{
	// Set order and dimension
	setTaylorOrder(taylorOrder);
	setDimension(dim);

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

void PhysicalEntity::setTaylorOrder(const int taylorOrder)
{
	if(taylorOrder < 0)
	{
		throw runtime_error("Invalid taylorOrder inserted. taylorOrder must be nonnegative.");
	}
	else
	{
		this->taylorOrder = taylorOrder;
		reservePositionOrientationMemory();
	}
}

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
	return this->position[0].dist(physicalEntity.position[0]);
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

void PhysicalEntity::setDimension(const int dim)
{
	if( (dim != 2) && (dim != 3))
	{
		throw runtime_error("Invalid dimension value inserted. Dimension must be 2 or 3.");
	}
	else
	{
		dimension = dim;
	}
}
