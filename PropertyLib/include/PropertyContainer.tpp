#ifndef PROPERTY_CONTAINER_TPP
#define PROPERTY_CONTAINER_TPP

// ---- Get, add and set properties ----

//	getValue:
//		Returns the value of a Property
template<typename interfaceType, typename storedType>
interfaceType PropertyContainer::getValue(const Property<interfaceType, storedType> & property) const
{
	std::set<string>::iterator it = propertyNames->find( property.getName() );

	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == property.getName()

		interfaceType value = property.getter( anyCast<storedType>( propertyValues->at(index) ) );

		return value;
	}
	else
	{
		return interfaceType();
	}
}

//	setProperty:
//		If property's name is already in propertyName, it's value is overwritten.
//		Otherwise, a new property is inserted.
template<typename interfaceType, typename storedType, typename implicitInterfaceType>
void PropertyContainer::setProperty(const Property<interfaceType, storedType> & property, const implicitInterfaceType & implicitValue )
{
	interfaceType value = interfaceType(implicitValue);
	std::set<string>::iterator it = propertyNames->find( property.getName() );

	// Checks if the desired property was already inserted
	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == property.getName()

		propertyValues->at(index) = value;
		inputMethods->at( index ) = property.inputMethod;
		outputMethods->at( index ) = property.outputMethod;
	}
	else	// Otherwise, a new property is inserted
	{
		std::pair< std::set<string>::iterator, bool > returnPair = propertyNames->insert( property.getName() );

		int index = std::distance( propertyNames->begin(), std::get<0>(returnPair) );	// Calculates the index where propertyNames[index] == property.getName()

		propertyValues->insert( propertyValues->begin() + index, value);
		inputMethods->insert( inputMethods->begin() + index, property.inputMethod );
		outputMethods->insert( outputMethods->begin() + index, property.outputMethod );
	}
}

#endif