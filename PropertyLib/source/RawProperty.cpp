#include <RawProperty.h>

RawProperty::RawProperty()
	: name("Nameless")
{
	if( std::is_same<interfaceType, storedType>::value )	// If both classes are equal, we can use default setter and getter functions
	{
		setter = defaultSetter;
		getter = defaultGetter;
	}
}

RawProperty::RawProperty(const string & name)
{
	this->setName(name);

	if( std::is_same<interfaceType, storedType>::value )	// If both classes are equal, we can use default setter and getter functions
	{
		setter = defaultSetter;
		getter = defaultGetter;
	}
}

