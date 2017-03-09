#ifndef PHYSICAL_ENTITY_TPP
#define PHYSICAL_ENTITY_TPP

// ---- Get, add and set properties ----
template< typename InterfaceType, typename storedType, typename implicitInterfaceType >
void PhysicalEntity::set( const Property<InterfaceType, storedType> & property, const implicitInterfaceType & value )
{
	propertyContainer.setProperty( property, value );
}

template<typename InterfaceType, typename storedType>
InterfaceType PhysicalEntity::get(const Property<InterfaceType, storedType> & property) const
{
	return propertyContainer.getValue( property );
}

#endif