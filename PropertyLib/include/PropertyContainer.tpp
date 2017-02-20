// ---- Constructors ----

// ---- Get, add and set properties ----

//	getProperty:
//		Returns a Property from propertyArray given its correspondent RawProperty.
//		In case this property does not exists, PropertyContainer::getProperty returns Property<interfaceType, storedType>(raw),
//		that is, a Property containing raw as its RawProperty correspondent and a value as created by the default constructor
//		of class interfaceType
template<typename interfaceType, typename storedType>
Property<interfaceType, storedType> PropertyContainer::getProperty(const RawProperty<interfaceType, storedType> & raw) const
{
	set<string>::iterator it = propertyNames->find( raw.getName() );

	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

		interfaceType value = raw.getter( boost::any_cast<storedType> propertyValues->at(index) );

		return Property<interfaceType, storedType>( raw, value );
	}
	else
	{
		return Property<interfaceType, storedType>( raw );
	}
}

//	getValue:
//		Returns the value of a Property given the Property's correspondent RawProperty
//		As an example, suppose that propertyArray contains a myMass object defined as
//			Property<double> myMass( mass, 50 )
//		Then, if there's no other property whose name is "mass" in propertyArray, the following code
//			std::cout << propertyArray.getValue(mass) << endl;
//		should print 50
template<typename interfaceType, typename storedType>
interfaceType PropertyContainer::getValue(const RawProperty<interfaceType, storedType> & raw) const
{
	return getProperty(raw).get(); 
}


//	setProperty:
//		If argument's name is already in propertyName, it's value is overwritten.
//		Otherwise, a new property is inserted.
/*template<typename interfaceType, typename storedType>
void PropertyContainer::setProperty(const RawProperty<interfaceType, storedType> & raw, const interfaceType & value )
{
	set<string>::iterator it = propertyNames->find( raw.getName() );

	// Checks if the desired property was already inserted
	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

		propertyValues->at(index) = value;
	}
	else	// Otherwise, a new property is inserted
	{
		std::pair< set<string>::iterator, bool > returnPair = propertyNames->insert( raw.getName() );

		int index = std::distance( propertyNames->begin(), std::get<0>(returnPair) );	// Calculates the index where propertyNames[index] == property.getName()

		propertyValues->insert( propertyValues->begin() + index, value);
	}
}*/

template<typename interfaceType, typename storedType, typename implicitInterfaceType>
void PropertyContainer::setProperty(const RawProperty<interfaceType, storedType> & raw, const implicitInterfaceType & pseudoValue )
{
	interfaceType value = interfaceType(pseudoValue);
	set<string>::iterator it = propertyNames->find( raw.getName() );

	// Checks if the desired property was already inserted
	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

		propertyValues->at(index) = value;
	}
	else	// Otherwise, a new property is inserted
	{
		std::pair< set<string>::iterator, bool > returnPair = propertyNames->insert( raw.getName() );

		int index = std::distance( propertyNames->begin(), std::get<0>(returnPair) );	// Calculates the index where propertyNames[index] == property.getName()

		propertyValues->insert( propertyValues->begin() + index, value);
	}
}

template<typename interfaceType, typename storedType>
void PropertyContainer::setProperty(const Property<interfaceType, storedType> & property)
{
	setProperty( property.getRawProperty(), property.getValue() );
}