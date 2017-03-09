#include <PropertyContainer.h>

PropertyContainer::PropertyContainer()
	: propertyValues( new Many ),
	settedValues( new std::map<string, bool> ),
	RawPropertyContainer()
{
}


PropertyContainer::PropertyContainer( const RawPropertyContainer & raw )
	: propertyValues( new Many ),
	settedValues( new std::map<string, bool> ),
	RawPropertyContainer( raw )
{
	this->propertyValues->resize( this->getPropertyNames()->size() );
}

void PropertyContainer::setProperty(const string & name, const Any & value )
{
	std::set<string>::iterator it = propertyNames->find( name );

	// Checks if the desired property was already inserted
	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

		propertyValues->at(index) = value;
		(*settedValues)[name] = true;
	}
	else	// Otherwise, a new property is inserted
	{
		std::pair< std::set<string>::iterator, bool > returnPair = propertyNames->insert( name );

		int index = std::distance( propertyNames->begin(), std::get<0>(returnPair) );	// Calculates the index where propertyNames[index] == property.getName()

		propertyValues->insert( propertyValues->begin() + index, value );
		(*settedValues)[name] = true;
	}
}

Any PropertyContainer::getValue(const string & name) const
{
	std::set<string>::iterator it = propertyNames->find( name );

	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

		return propertyValues->at(index);
	}
	else
	{
		return Any();
	}	
}

bool PropertyContainer::checkSetted(const string & propertyName)
{
	return (*settedValues)[propertyName];
}