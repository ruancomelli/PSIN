#ifndef PROPERTY_CONTAINER_TPP
#define PROPERTY_CONTAINER_TPP

// ---- Get, add and set properties ----

//	getValue:
//		Returns the value of a Property
template<typename InterfaceType, typename StoredType>
InterfaceType PropertyContainer::getValue(const Property<InterfaceType, StoredType> & property) const
{
	string propertyName = property.getName();

	std::set<string>::iterator it = propertyNames->find( propertyName );

	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		auto anyValue = (*propertyValues)[propertyName];
		StoredType storedValue = anyCast<StoredType>( anyValue );
		InterfaceType value = property.getter( storedValue );

		return value;
	}
	else
	{
		return InterfaceType();	// This line should be improved
	}
}

//	setProperty:
//		If property's name is already in propertyName, it's value is overwritten.
//		Otherwise, a new property is inserted.
template<typename InterfaceType, typename StoredType, typename implicitInterfaceType>
void PropertyContainer::setProperty(const Property<InterfaceType, StoredType> & property, const implicitInterfaceType & implicitValue )
{
	InterfaceType value = InterfaceType(implicitValue);
	string propertyName = property.getName();
	
	propertyNames->insert( propertyName );

	(*propertyValues)[propertyName] = value;
	(*inputMethods)[propertyName] = property.inputMethod;
	(*outputMethods)[propertyName] = property.outputMethod;
	(*settedFlag)[propertyName] = true;
}

template<typename InterfaceType, typename StoredType>
bool PropertyContainer::checkSetted(const Property<InterfaceType, StoredType> & property)
{
	return (*settedFlag)[ property.getName() ];
}

#endif
