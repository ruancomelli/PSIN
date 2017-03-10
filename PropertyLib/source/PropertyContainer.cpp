#include <PropertyContainer.h>

PropertyContainer::PropertyContainer()
	: propertyValues( new std::map<string, Any> ),
	settedFlag( new std::map<string, bool> ),
	RawPropertyContainer()
{
}


PropertyContainer::PropertyContainer( const RawPropertyContainer & raw )
	: propertyValues( new std::map<string, Any> ),
	settedFlag( new std::map<string, bool> ),
	RawPropertyContainer( raw )
{
}

void PropertyContainer::setProperty(const string & name, const Any & value )	// This throws an exception if the desired property was not inserted yet
{
	propertyValues->at(name) = value;
	settedFlag->at(name) = true;
}

Any PropertyContainer::getValue(const string & name) const
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

bool PropertyContainer::checkSetted(const string & propertyName)
{
	return (*settedFlag)[propertyName];
}