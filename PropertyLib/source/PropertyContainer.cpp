#include <PropertyContainer.h>

PropertyContainer::PropertyContainer()
	: propertyValues( new many ),
	propertyNames( new set<string> )
{
}

PropertyContainer::PropertyContainer( many & propValues, set<string> & propNames )
	: propertyValues( &propValues ),
	propertyNames( &propNames )
{
}

void PropertyContainer::pointPropertyValues( many & propValues )
{
	this->propertyValues = SharedPointer<many>( &propValues );
}

void PropertyContainer::pointPropertyNames( set<string> & propNames )
{
	this->propertyNames = SharedPointer< set<string> >( &propNames );
}