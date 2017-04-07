#include <ValuedPropertyContainer.hpp>

ValuedPropertyContainer::ValuedPropertyContainer()
	: propertyValues( new std::map<string, Any> ),
	settedFlag( new std::map<string, bool> ),
	PropertyContainer()
{
}


ValuedPropertyContainer::ValuedPropertyContainer( const PropertyContainer & raw )
	: propertyValues( new std::map<string, Any> ),
	settedFlag( new std::map<string, bool> ),
	PropertyContainer( raw )
{
}

void ValuedPropertyContainer::setProperty(const string & name, const Any & value )	// This throws an exception if the desired property was not inserted yet
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

Any ValuedPropertyContainer::getValue(const string & name) const
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

bool ValuedPropertyContainer::checkSetted(const string & propertyName)
{
	return (*settedFlag)[propertyName];
}