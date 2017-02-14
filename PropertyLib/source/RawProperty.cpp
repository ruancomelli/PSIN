#include <RawProperty.h>

// Constructors
template<typename interfaceType, typename storedType>
RawProperty<interfaceType, storedType>::RawProperty()
	: name("Nameless")
{
	if( std::is_same<interfaceType, storedType>::value )	// If both classes are equal, we can use default setter and getter functions
	{
		setter = defaultSetter;
		getter = defaultGetter;
	}
}

template<typename interfaceType, typename storedType>
RawProperty<interfaceType, storedType>::RawProperty(const string & name)
{
	this->setName(name);

	if( std::is_same<interfaceType, storedType>::value )	// If both classes are equal, we can use default setter and getter functions
	{
		setter = defaultSetter;
		getter = defaultGetter;
	}
}

template<typename interfaceType, typename storedType>
RawProperty<interfaceType, storedType>::RawProperty(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &))
{
	this->name = name;
	this->setter = setterFunction;
	this->getter = getterFunction;
}


// Set and get name

template<typename interfaceType, typename storedType>
void RawProperty<interfaceType, storedType>::setName(const string & name)
{
	if(!name.empty()) this->name = name;
	else this->name = "Nameless";
}

template<typename interfaceType, typename storedType>
string RawProperty<interfaceType, storedType>::getName(void) const
{
	return this->name;
}


// Set setter and getter
template<typename interfaceType, typename storedType>
void RawProperty<interfaceType, storedType>::setSetterFunction( void (*setterFunction)(const interfaceType & value, storedType & destination) )
{
	this->setter = setterFunction;
}

template<typename interfaceType, typename storedType>
void RawProperty<interfaceType, storedType>::setGetterFunction( interfaceType (*getterFunction)(const storedType & value) )
{
	this->getter = getterFunction;
}