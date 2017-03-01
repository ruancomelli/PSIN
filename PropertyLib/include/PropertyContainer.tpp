// ---- Constructors ----

// ---- Get, add and set properties ----

//	getValue:
//		Returns the value of a Property
template<typename interfaceType, typename storedType>
interfaceType PropertyContainer::getValue(const Property<interfaceType, storedType> & raw) const
{
	set<string>::iterator it = propertyNames->find( raw.getName() );

	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

		interfaceType value = raw.getter( anyCast<storedType>( propertyValues->at(index) ) );

		return value;
	}
	else
	{
		return interfaceType();
	}
}

//	setProperty:
//		If argument's name is already in propertyName, it's value is overwritten.
//		Otherwise, a new property is inserted.
template<typename interfaceType, typename storedType, typename implicitInterfaceType>
void PropertyContainer::setProperty(const Property<interfaceType, storedType> & raw, const implicitInterfaceType & implicitValue )
{
	interfaceType value = interfaceType(implicitValue);
	set<string>::iterator it = propertyNames->find( raw.getName() );

	// Checks if the desired property was already inserted
	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

		propertyValues->at(index) = value;
		inputMethods->at( index ) = raw.inputMethod;
		outputMethods->at( index ) = raw.outputMethod;
	}
	else	// Otherwise, a new property is inserted
	{
		std::pair< set<string>::iterator, bool > returnPair = propertyNames->insert( raw.getName() );

		int index = std::distance( propertyNames->begin(), std::get<0>(returnPair) );	// Calculates the index where propertyNames[index] == property.getName()

		propertyValues->insert( propertyValues->begin() + index, value);
		inputMethods->insert( inputMethods->begin() + index, raw.inputMethod );
		outputMethods->insert( outputMethods->begin() + index, raw.outputMethod );
	}
}