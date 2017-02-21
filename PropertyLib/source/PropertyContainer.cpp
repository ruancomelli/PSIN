#include <PropertyContainer.h>

PropertyContainer::PropertyContainer()
	: propertyValues( new many ),
	propertyNames( new set<string> )
{
}