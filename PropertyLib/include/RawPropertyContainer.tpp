//	addProperty:
//		If argument's name is already in propertyName, its input and output methods are overwritten.
//		Otherwise, a new property is inserted.
template<typename interfaceType, typename storedType>
void RawPropertyContainer::addProperty(const Property<interfaceType, storedType> & raw)
{
	set<string>::iterator it = propertyNames->find( raw.getName() );

	// Checks if the desired property was already inserted
	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

		inputMethods->at( index ) = raw.inputMethod;
		outputMethods->at( index ) = raw.outputMethod;
	}
	else	// Otherwise, a new property is inserted
	{
		std::pair< set<string>::iterator, bool > returnPair = propertyNames->insert( raw.getName() );

		int index = std::distance( propertyNames->begin(), std::get<0>(returnPair) );	// Calculates the index where propertyNames[index] == property.getName()

		inputMethods->insert( inputMethods->begin() + index, raw.inputMethod );
		outputMethods->insert( outputMethods->begin() + index, raw.outputMethod );
	}
}