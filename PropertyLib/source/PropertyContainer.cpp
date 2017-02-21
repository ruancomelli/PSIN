#include <PropertyContainer.h>

PropertyContainer::PropertyContainer()
	: propertyValues( new many ),
	propertyNames( new set<string> ),
	inputMethods( new vector<inputMethodType> ),
	outputMethods( new vector<outputMethodType> )
{
}

set<string> PropertyContainer::getPropertyNames(void)
{
	return *(this->propertyNames);
}