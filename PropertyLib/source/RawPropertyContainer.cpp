#include <RawPropertyContainer.h>

RawPropertyContainer::RawPropertyContainer()
	: propertyNames( new std::set<string> ),
	inputMethods( new std::map< string, InputMethodType > ),
	outputMethods( new std::map< string, OutputMethodType > )
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
	return inputMethods->at( rawName );
}

RawPropertyContainer::OutputMethodType RawPropertyContainer::getOutputMethod(const string & rawName ) const
{
	return outputMethods->at( rawName );
}