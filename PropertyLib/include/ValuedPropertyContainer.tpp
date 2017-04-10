#ifndef VALUED_PROPERTY_CONTAINER_TPP
#define VALUED_PROPERTY_CONTAINER_TPP

// ----- Constructors -----
template<typename ... PropertyTypes>
ValuedPropertyContainer<PropertyTypes...>::ValuedPropertyContainer()
	: propertyValues( new std::map<string, Any> ),
	settedFlag( new std::map<string, bool> ),
	PropertyContainer<PropertyTypes...>::PropertyContainer()
{
}

template<typename ... PropertyTypes>
ValuedPropertyContainer<PropertyTypes...>::ValuedPropertyContainer( const PropertyContainer<PropertyTypes...> & propertyContainer )
	: propertyValues( new std::map<string, Any> ),
	settedFlag( new std::map<string, bool> ),
	PropertyContainer<PropertyTypes...>::PropertyContainer( propertyContainer )
{
}

// ---- Get, add and set properties ----

//	getValue:
//		Returns the value of a Property
template<typename ... PropertyTypes>
template<typename InterfaceType, typename StoredType>
InterfaceType ValuedPropertyContainer<PropertyTypes...>::getValue(const Property<InterfaceType, StoredType> & property) const
{
	string propertyName = property.getName();

	std::set<string>::iterator it = this->propertyNames->find( propertyName );

	if( it != this->propertyNames->end() )	// In this case, the search was successfull
	{
		auto anyValue = (*this->propertyValues)[propertyName];
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
template<typename ... PropertyTypes>
template<typename InterfaceType, typename StoredType, typename implicitInterfaceType>
void ValuedPropertyContainer<PropertyTypes...>::setProperty(const Property<InterfaceType, StoredType> & property, const implicitInterfaceType & implicitValue )
{
	InterfaceType value = InterfaceType(implicitValue);
	string propertyName = property.getName();
	
	this->propertyNames->insert( propertyName );

	(*this->propertyValues)[propertyName] = value;
	(*this->inputMethods)[propertyName] = property.inputMethod;
	(*this->outputMethods)[propertyName] = property.outputMethod;
	(*this->settedFlag)[propertyName] = true;
}

template<typename ... PropertyTypes>
void ValuedPropertyContainer<PropertyTypes...>::setProperty(const string & name, const Any & value )	// This throws an exception if the desired property was not inserted yet
{
	std::set<string>::iterator it = propertyNames->find( name ); 
 
	if( it != propertyNames->end() ) 
	{ 
		(*propertyValues)[name] = value; 
		(*settedFlag)[name] = true; 
	} 
	else 
	{ 
		propertyValues->at(name) = value; 
		settedFlag->at(name) = true; 
	} 
}

template<typename ... PropertyTypes>
Any ValuedPropertyContainer<PropertyTypes...>::getValue(const string & name) const
{
	std::set<string>::iterator it = propertyNames->find( name );

	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		return (*propertyValues)[name];
	}
	else
	{
		return Any();	// This line should be improved.
	}	
}


// ----- Checking -----
template<typename ... PropertyTypes>
template<typename InterfaceType, typename StoredType>
bool ValuedPropertyContainer<PropertyTypes...>::checkSetted(const Property<InterfaceType, StoredType> & property)
{
	return (*settedFlag)[ property.getName() ];
}
template<typename ... PropertyTypes>
bool ValuedPropertyContainer<PropertyTypes...>::checkSetted(const string & propertyName)
{
	return (*settedFlag)[propertyName];
}

#endif // VALUED_PROPERTY_CONTAINER_TPP
