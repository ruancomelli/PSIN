#include <RawPropertyContainer.h>

RawPropertyContainer::RawPropertyContainer()
	: propertyNames( new set<string> ),
	inputMethods( new vector<inputMethodType> ),
	outputMethods( new vector<outputMethodType> )
{
}

RawPropertyContainer::RawPropertyContainer( const RawPropertyContainer & other)
	: propertyNames( other.propertyNames ),
	inputMethods( other.inputMethods ),
	outputMethods( other.outputMethods )
{
}

SharedPointer<set<string>> RawPropertyContainer::getPropertyNames(void) const
{
	return this->propertyNames;
}

RawPropertyContainer::inputMethodType RawPropertyContainer::getInputMethod(const string & rawName ) const
{
	set<string>::iterator it = propertyNames->find( rawName );

	int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

	return inputMethods->at( index );
}

RawPropertyContainer::outputMethodType RawPropertyContainer::getOutputMethod(const string & rawName ) const
{
	set<string>::iterator it = propertyNames->find( rawName );

	int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

	return outputMethods->at( index );
}