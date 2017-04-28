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
template<typename ... PropertyTypes>
template<typename PropertyType, typename Ret, typename ... Args>
Ret PropertyContainer<PropertyTypes...>::call(std::function<Ret(PropertyType &, Args...)> functionToCall, Args ... args)
{
	static_assert(type_is_in_list<PropertyType, PropertyTypes...>::value, 
		"Error: Cannot call call<PropertyType> when PropertyType is not a template parameter in the definition of a PropertyContainer\n");

	return functionToCall(std::get<PropertyType>(property), args...);
}

template<typename ... PropertyTypes>
template<typename PropertyType, typename Ret, typename ... Args>
Ret PropertyContainer<PropertyTypes...>::call( Ret (PropertyType::* functionToCall)(Args...), Args ... args)
{
	std::function<Ret(PropertyType &, Args...)> f = functionToCall;

	return call(f, args...);
}

#endif // PROPERTY_CONTAINER_H
