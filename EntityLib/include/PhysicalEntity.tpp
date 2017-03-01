// ---- Constructors ----

// ---- Get, add and set properties ----


template< typename interfaceType, typename storedType, typename implicitInterfaceType >
void PhysicalEntity::set( const RawProperty<interfaceType, storedType> & raw, const implicitInterfaceType & value )
{
	propertyContainer.setProperty( raw, value );
}

template<typename interfaceType, typename storedType>
interfaceType PhysicalEntity::get(const RawProperty<interfaceType, storedType> & raw) const
{
	return propertyContainer.getValue( raw );
}