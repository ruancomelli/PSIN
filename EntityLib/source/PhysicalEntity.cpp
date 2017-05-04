// #include <PhysicalEntity.hpp>

// // Standard
// #include <stdexcept>

// // PropertyLib
// #include <PropertyDefinitions.hpp>

// using std::string;
// using std::vector;

// // ------------------------------- Constructors -------------------------------
// int PhysicalEntity::dimension = 3;

// PhysicalEntity::PhysicalEntity()
// 	: Entity(), 
// 	geometry(DEFAULT)
// {
// 	setTaylorOrder(3); // It calls resizePositionOrientation
// 	setDimension(3);

// 	set( PropertyDefinitions::mass, 1 );
// 	set( PropertyDefinitions::moment_of_inertia , 1 );
// }

// PhysicalEntity::PhysicalEntity( const Entity & base )
// 	: Entity(base), geometry(DEFAULT)
// {
// 	setTaylorOrder(3);
// 	setDimension(3);

// 	set(PropertyDefinitions::mass, 1 );
// 	set(PropertyDefinitions::moment_of_inertia, 1 );
// }

// PhysicalEntity::PhysicalEntity(const int taylorOrder, const int dim, const int handle)
// 	: Entity(handle), geometry(DEFAULT)
// {
// 	// Set order and dimension
// 	setTaylorOrder(taylorOrder);
// 	setDimension(dim);

// 	set(PropertyDefinitions::mass, 1 );
// 	set(PropertyDefinitions::moment_of_inertia , 1 );
// }

// PhysicalEntity::PhysicalEntity(const int taylorOrder, const int dim,  const Entity & base)
// 	: Entity(base), geometry(DEFAULT)
// {
// 	setTaylorOrder(taylorOrder);
// 	setDimension(dim);
	
// 	set(PropertyDefinitions::mass, 1 );
// 	set(PropertyDefinitions::moment_of_inertia , 1 );
// }
// // ------------------------------- Property -------------------------------

// void PhysicalEntity::requireProperties( const PropertyContainer & raw )
// {
// 	this->propertyContainer = ValuedPropertyContainer(raw);
// }

// 	// dimension
// int PhysicalEntity::getDimension(void) const
// {
// 	return this->dimension;
// }

// 	// taylorOrder
// void PhysicalEntity::setTaylorOrder(const int taylorOrder)
// {
// 	if(taylorOrder < 3 || taylorOrder > 5)
// 	{
// 		throw std::runtime_error("Invalid taylorOrder inserted. taylorOrder must be either 3, 4 or 5.");
// 	}
// 	else
// 	{
// 		this->taylorOrder = taylorOrder;
// 		resizePositionOrientation();
// 	}
// }

// int PhysicalEntity::getTaylorOrder(void) const
// {
// 	return this->taylorOrder;
// }

// SharedPointer<std::set<string>> PhysicalEntity::getPropertyNames( void ) const
// {
// 	return this->propertyContainer.getPropertyNames();
// }

// void PhysicalEntity::set( const string & rawName, const Any & value )
// {
// 	this->propertyContainer.setProperty( rawName, value );
// }

// Any PhysicalEntity::getAsAnyValue( const string & name ) const
// {
// 	return this->propertyContainer.getValue(name);
// }
// //------------------------------- Position -------------------------------

// // ------------------------------- Orientation -------------------------------

// // ------------------------------- Geometry -------------------------------
// void PhysicalEntity::setGeometry(const GeometryType geometry)
// {
// 	this->geometry = geometry;
	
// 	return;
// }

// GeometryType PhysicalEntity::getGeometry() const
// {
// 	return this->geometry;
// }

// // ------------------------------- Auxiliar Functions -------------------------------

// void PhysicalEntity::resizePositionOrientation(void)
// {
// 	int size = taylorOrder + 1;
// 	this->position.resize(size);
// 	this->orientation.resize(size);
// }

// void PhysicalEntity::setDimension(const int dim)
// {
// 	if( (dim != 2) && (dim != 3))
// 	{
// 		throw std::runtime_error("Invalid dimension value inserted. Dimension must be either 2 or 3.");
// 	}
// 	else
// 	{
// 		dimension = dim;
// 	}
// }


