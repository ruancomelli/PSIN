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

		interfaceType value = raw.getter( boost::any_cast<storedType> (*propertyValues)[index] );

		return Property<interfaceType, storedType>( raw, value );
	}
	else
	{
		return Property<interfaceType, storedType>(raw);
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
//		If argument property is already in propertyArray, it is overwritten.
//		Otherwise, property is inserted into propertyArray.
template<typename interfaceType, typename storedType>
void PropertyContainer::setProperty(const Property<interfaceType, storedType> & property)
{
	set<string>::iterator it = propertyNames->find( property.getName() );

	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames.begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()


		// Correct this:
		propertyArray[index] = property;
	}
	else
	{
		// Correct this:
		std::pair< set<string>::iterator, bool > returnPair = propertyNames.insert( property.getName() );
		index = std::distance( propertyNames.begin(), std::get<0>(returnPair) );	// Calculates the index where propertyNames[index] == raw.getName()

		propertyArray.insert(index, property);
	}
}
