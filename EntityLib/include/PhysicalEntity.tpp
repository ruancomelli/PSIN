#ifndef PHYSICAL_ENTITY_TPP
#define PHYSICAL_ENTITY_TPP

// ---- Get, add and set properties ----
template< typename interfaceType, typename storedType, typename implicitInterfaceType >
void PhysicalEntity::set( const Property<interfaceType, storedType> & raw, const implicitInterfaceType & value )
{
	propertyContainer.setProperty( raw, value );
}

template<typename interfaceType, typename storedType>
interfaceType PhysicalEntity::get(const Property<interfaceType, storedType> & raw) const
{
	return propertyContainer.getValue( raw );
}

#endif