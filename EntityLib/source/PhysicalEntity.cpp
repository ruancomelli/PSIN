#include <PhysicalEntity.h>

// ------------------------------- Constructor -------------------------------
int PhysicalEntity::dimension = 3;

PhysicalEntity::PhysicalEntity()
	: Entity(), geometry(DEFAULT)
{
	setTaylorOrder(3); // It calls resizePositionOrientation
	setDimension(3);

	// Initialize Properties
	resizePropertyVector();
}

PhysicalEntity::PhysicalEntity( const Entity & base )
	: Entity(base), geometry(DEFAULT)
{
	setTaylorOrder(3);
	setDimension(3);

	// Initialize Properties
	resizePropertyVector();
}

PhysicalEntity::PhysicalEntity(const int taylorOrder, const int dim, const int handle)
	: Entity(handle), geometry(DEFAULT)
{
	// Set order and dimension
	setTaylorOrder(taylorOrder);
	setDimension(dim);

	// Alloc memory to properties
	resizePropertyVector();
}

PhysicalEntity::PhysicalEntity(const int taylorOrder, const int dim,  const Entity & base)
	: Entity(base), geometry(DEFAULT)
{
	setTaylorOrder(taylorOrder);
	setDimension(dim);

	// Initialize Properties
	resizePropertyVector();
}
// ------------------------------- Property -------------------------------

	// dimension
int PhysicalEntity::getDimension(void) const
{
	return this->dimension;
}

	// taylorOrder
void PhysicalEntity::setTaylorOrder(const int taylorOrder)
{
	if(taylorOrder < 0)
	{
		throw runtime_error("Invalid taylorOrder inserted. taylorOrder must be nonnegative.");
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

	// scalarProperty
void PhysicalEntity::setScalarProperty(const int scalarPropertyIdentifier, const double scalarPropertyValue)
{
	this->scalarProperty[scalarPropertyIdentifier] = scalarPropertyValue;
}

void PhysicalEntity::setScalarProperty(const DoubleVector scalarPropertyVector)
{
	if( scalarPropertyVector.size() != N_SCALAR_PROPERTY )
		throw runtime_error("size of scalarPropertyVector is not N_SCALAR_PROPERTY, function setScalarProperty");

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

// ------------------------------- Distance and Touching -------------------------------
double PhysicalEntity::distance(PhysicalEntityPtr physicalEntity){
	return this->position[0].dist(physicalEntity->position[0]);
}

// ------------------------------- Auxiliar Functions -------------------------------

void PhysicalEntity::resizePositionOrientation(void)
{
	int size = taylorOrder + 1;
	this->position.resize(size);
	this->orientation.resize(size);
}

void PhysicalEntity::resizePropertyVector(void)
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
		throw runtime_error("taylorOrder does not agree in function PhysicalEntity::setSpatial(vector<Vector3D> & spatialToSet, const vector<Vector3D> & spatial)");
	}
	spatialToSet = spatial;
}
