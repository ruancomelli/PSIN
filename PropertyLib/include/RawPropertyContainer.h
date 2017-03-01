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
#include <list>
#include <vector>

using namespace std;

class RawPropertyContainer
{
	public:
		typedef bool (*inputMethodType)(ifstream & in, Any & value);
		typedef bool (*outputMethodType)(ofstream & in, Any & value);

		// ---- Get, add and set properties and values ----
		RawPropertyContainer();
		RawPropertyContainer( const RawPropertyContainer & other);

		// Get a property's input method
		inputMethodType getInputMethod(const string & rawName) const;

		// Get a property's output method
		outputMethodType getOutputMethod(const string & rawName) const;

		template<typename interfaceType, typename storedType>
		void addProperty(const Property<interfaceType, storedType> & raw );

		SharedPointer<set<string>> getPropertyNames(void) const;

	protected:
		SharedPointer< set<string> > propertyNames;
		SharedPointer< std::vector< inputMethodType > > inputMethods;
		SharedPointer< std::vector< outputMethodType > > outputMethods;
}; // class RawPropertyContainer

#include <RawPropertyContainer.tpp>

#endif