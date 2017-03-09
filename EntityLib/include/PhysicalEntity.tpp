#ifndef PHYSICAL_ENTITY_TPP
#define PHYSICAL_ENTITY_TPP

// ---- Get, add and set properties ----
template< typename InterfaceType, typename StoredType, typename implicitInterfaceType >
void PhysicalEntity::set( const Property<InterfaceType, StoredType> & property, const implicitInterfaceType & value )
{
	propertyContainer.setProperty( property, value );
}

template<typename InterfaceType, typename StoredType>
InterfaceType PhysicalEntity::get(const Property<InterfaceType, StoredType> & property) const
{
	return propertyContainer.getValue( property );
}

#endif