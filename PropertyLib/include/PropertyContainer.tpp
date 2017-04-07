#ifndef PROPERTY_CONTAINER_TPP
#define PROPERTY_CONTAINER_TPP

//	insertProperty:
//		If argument's name is already in propertyName, its input and output methods are overwritten.
//		Otherwise, a new property is inserted.

// template<typename InterfaceType, typename StoredType>
template<typename ... PropertyTypes>
template<typename InterfaceType, typename StoredType>
void PropertyContainer<PropertyTypes...>::insertProperty(const Property<InterfaceType, StoredType> & property)
{
	using string = std::string;

	string propertyName = property.getName();

	std::set<string>::iterator it = this->propertyNames->find( property.getName() );

	this->propertyNames->insert( propertyName );

	(*inputMethods)[propertyName] = property.inputMethod;
	(*outputMethods)[propertyName] = property.outputMethod;
}

template<typename ... PropertyTypes>
PropertyContainer<PropertyTypes...>::PropertyContainer()
	: propertyNames( new std::set<std::string> ),
	inputMethods( new std::map<std::string, InputMethodType> ),
	outputMethods( new std::map<std::string, OutputMethodType> )
{
}

template<typename ... PropertyTypes>
PropertyContainer<PropertyTypes...>::PropertyContainer( const PropertyContainer & other)
	: propertyNames( other.propertyNames ),
	inputMethods( other.inputMethods ),
	outputMethods( other.outputMethods )
{
}

template<typename ... PropertyTypes>
SharedPointer< std::set<std::string> > PropertyContainer<PropertyTypes...>::getPropertyNames(void) const
{
	return this->propertyNames;
}

template<typename ... PropertyTypes>
typename PropertyContainer<PropertyTypes...>::InputMethodType	PropertyContainer<PropertyTypes...>::getInputMethod(const std::string & rawName ) const
{
	return inputMethods->at( rawName );
}

template<typename ... PropertyTypes>
typename PropertyContainer<PropertyTypes...>::OutputMethodType	PropertyContainer<PropertyTypes...>::getOutputMethod(const std::string & rawName ) const
{
	return outputMethods->at( rawName );
}

#endif // PROPERTY_CONTAINER_H
