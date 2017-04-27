#ifndef PROPERTY_CONTAINER_TPP
#define PROPERTY_CONTAINER_TPP

// ----- Constructors -----
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

// ----- Insert Property -----
template<typename ... PropertyTypes>
template<typename Property>
void PropertyContainer<PropertyTypes...>::insertProperty(void)
{
	using string = std::string;

	string propertyName = Property().getName();

	std::set<string>::iterator it = this->propertyNames->find( propertyName );

	this->propertyNames->insert( propertyName );

	(*inputMethods)[propertyName] = Property().inputMethod;
	(*outputMethods)[propertyName] = Property().outputMethod;
}

// ----- Get property names, input methods and output methods
template<typename ... PropertyTypes>
SharedPointer< std::set<std::string> > PropertyContainer<PropertyTypes...>::getPropertyNames(void) const
{
	return this->propertyNames;
}

template<typename ... PropertyTypes>
typename PropertyContainer<PropertyTypes...>::InputMethodType PropertyContainer<PropertyTypes...>::getInputMethod(const std::string & rawName ) const
{
	return inputMethods->at( rawName );
}

template<typename ... PropertyTypes>
typename PropertyContainer<PropertyTypes...>::OutputMethodType PropertyContainer<PropertyTypes...>::getOutputMethod(const std::string & rawName ) const
{
	return outputMethods->at( rawName );
}



///////////////////////////// NEW /////////////////////////////

// Get property
template<typename ... PropertyTypes>
template<typename PropertyType>
PropertyType PropertyContainer<PropertyTypes...>::get() const
{
	static_assert(/*Check that PropertyType is in PropertyTypes...*/);

	return std::get<PropertyType>(this->property);
}

#endif // PROPERTY_CONTAINER_H
