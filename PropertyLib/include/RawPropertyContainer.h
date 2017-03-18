#ifndef RAW_PROPERTY_CONTAINER_H
#define RAW_PROPERTY_CONTAINER_H

// PropertyLib
#include <Property.h>

// UtilsLib
#include <Any.h>

// Standard
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <set>

using std::string;

class RawPropertyContainer
{
	public:
		using InputMethodType = std::function< bool(std::ifstream & in, Any & value) >;
		using OutputMethodType = std::function< bool(std::ofstream & in, Any & value) >;

		// ---- Get, add and set properties and values ----
		RawPropertyContainer();
		RawPropertyContainer( const RawPropertyContainer & other);

		// Get a property's input method
		InputMethodType getInputMethod(const string & name) const;

		// Get a property's output method
		OutputMethodType getOutputMethod(const string & name) const;

		template<typename InterfaceType, typename StoredType>
		void addProperty(const Property<InterfaceType, StoredType> & property );

		SharedPointer< std::set<string> > getPropertyNames(void) const;

	protected:
		SharedPointer< std::set<string> > propertyNames;
		SharedPointer< std::map< string, InputMethodType > > inputMethods;
		SharedPointer< std::map< string, OutputMethodType > > outputMethods;
}; // class RawPropertyContainer

#include <RawPropertyContainer.tpp>

#endif