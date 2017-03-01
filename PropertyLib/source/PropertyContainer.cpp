#include <PropertyContainer.h>

PropertyContainer::PropertyContainer()
	: propertyValues( new many ),
	RawPropertyContainer()
{
}


PropertyContainer::PropertyContainer( const RawPropertyContainer & raw )
	: propertyValues( new many ),
	RawPropertyContainer( raw )
{
	this->propertyValues->resize( this->getPropertyNames()->size() );
}

void PropertyContainer::setProperty(const string & rawName, const boost::any & value )
{
	set<string>::iterator it = propertyNames->find( rawName );

	// Checks if the desired property was already inserted
	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

		propertyValues->at(index) = value;
	}
	else	// Otherwise, a new property is inserted
	{
		std::pair< set<string>::iterator, bool > returnPair = propertyNames->insert( rawName );

		int index = std::distance( propertyNames->begin(), std::get<0>(returnPair) );	// Calculates the index where propertyNames[index] == property.getName()

		propertyValues->insert( propertyValues->begin() + index, value);
	}
}

boost::any PropertyContainer::getValue(const string & rawName) const
{
	set<string>::iterator it = propertyNames->find( rawName );

	if( it != propertyNames->end() )	// In this case, the search was successfull
	{
		int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

		return propertyValues->at(index);
	}
	else
	{
		return boost::any();
	}	
}