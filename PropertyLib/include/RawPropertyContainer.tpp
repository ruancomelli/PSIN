#ifndef RAW_PROPERTY_CONTAINER_TPP
#define RAW_PROPERTY_CONTAINER_TPP

//	addProperty:
//		If argument's name is already in propertyName, its input and output methods are overwritten.
//		Otherwise, a new property is inserted.
template<typename InterfaceType, typename StoredType>
void RawPropertyContainer::addProperty(const Property<InterfaceType, StoredType> & property)
{
	string propertyName = property.getName();

	std::set<string>::iterator it = propertyNames->find( property.getName() );

	// Checks if the desired property was already inserted
	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		(*inputMethods)[propertyName] = property.inputMethod;
		(*outputMethods)[propertyName] = property.outputMethod;
	}
	else	// Otherwise, a new property is inserted
	{
		std::pair< set<string>::iterator, bool > returnPair = propertyNames->insert( property.getName() );

		int index = std::distance( propertyNames->begin(), std::get<0>(returnPair) );	// Calculates the index where propertyNames[index] == property.getName()

		inputMethods->insert( inputMethods->begin() + index, property.inputMethod );
		outputMethods->insert( outputMethods->begin() + index, property.outputMethod );
	}
}

#endif