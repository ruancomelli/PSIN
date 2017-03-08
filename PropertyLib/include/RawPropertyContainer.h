#ifndef RAW_PROPERTY_CONTAINER_H
#define RAW_PROPERTY_CONTAINER_H

// PropertyLib
#include <Property.h>

// UtilsLib
#include <Any.h>

// Standard
#include <iostream>
#include <string>
#include <set>
#include <vector>

using std::vector;
using std::string;

class RawPropertyContainer
{
	public:
		typedef bool (*inputMethodType)(std::ifstream & in, Any & value);
		typedef bool (*outputMethodType)(std::ofstream & in, Any & value);

		// ---- Get, add and set properties and values ----
		RawPropertyContainer();
		RawPropertyContainer( const RawPropertyContainer & other);

		// Get a property's input method
		inputMethodType getInputMethod(const string & name) const;

		// Get a property's output method
		outputMethodType getOutputMethod(const string & name) const;

		template<typename interfaceType, typename storedType>
		void addProperty(const Property<interfaceType, storedType> & property );

		SharedPointer< std::set<string> > getPropertyNames(void) const;

	protected:
		SharedPointer< std::set<string> > propertyNames;
		SharedPointer< vector< inputMethodType > > inputMethods;
		SharedPointer< vector< outputMethodType > > outputMethods;
}; // class RawPropertyContainer

#include <RawPropertyContainer.tpp>

#endif