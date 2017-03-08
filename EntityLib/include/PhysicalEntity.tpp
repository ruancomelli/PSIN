#ifndef PHYSICAL_ENTITY_TPP
#define PHYSICAL_ENTITY_TPP

// ---- Get, add and set properties ----
template< typename interfaceType, typename storedType, typename implicitInterfaceType >
void PhysicalEntity::set( const Property<interfaceType, storedType> & property, const implicitInterfaceType & value )
{
	propertyContainer.setProperty( property, value );
}

template<typename interfaceType, typename storedType>
interfaceType PhysicalEntity::get(const Property<interfaceType, storedType> & property) const
{
	return propertyContainer.getValue( property );
}

#endif