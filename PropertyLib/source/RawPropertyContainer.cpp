#include <RawPropertyContainer.h>

RawPropertyContainer::RawPropertyContainer()
	: propertyNames( new std::set<string> ),
	inputMethods( new vector<InputMethodType> ),
	outputMethods( new vector<OutputMethodType> )
{
}

RawPropertyContainer::RawPropertyContainer( const RawPropertyContainer & other)
	: propertyNames( other.propertyNames ),
	inputMethods( other.inputMethods ),
	outputMethods( other.outputMethods )
{
}

SharedPointer< std::set<string> > RawPropertyContainer::getPropertyNames(void) const
{
	return this->propertyNames;
}

RawPropertyContainer::InputMethodType RawPropertyContainer::getInputMethod(const string & rawName ) const
{
	std::set<string>::iterator it = propertyNames->find( rawName );

	int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

	return inputMethods->at( index );
}

RawPropertyContainer::OutputMethodType RawPropertyContainer::getOutputMethod(const string & rawName ) const
{
	std::set<string>::iterator it = propertyNames->find( rawName );

	int index = std::distance( propertyNames->begin(), it );	// Calculates the index where propertyNames[index] == raw.getName()

	return outputMethods->at( index );
}