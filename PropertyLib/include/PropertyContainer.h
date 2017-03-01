#ifndef PROPERTY_CONTAINER_H
#define PROPERTY_CONTAINER_H

// PropertyLib
#include <RawPropertyContainer.h>

// Standard
#include <iostream>
#include <string>
#include <set>
#include <list>
#include <vector>

// UtilsLib
#include <Any.h>

using namespace std;

class PropertyContainer : public RawPropertyContainer
{
	public:
		typedef bool (*inputMethodType)(ifstream & in, Any & value);
		typedef bool (*outputMethodType)(ofstream & in, Any & value);

		// ---- Get, add and set properties and values ----
		PropertyContainer();
		explicit PropertyContainer( const RawPropertyContainer & raw );

		// Get a property's value
		template<typename interfaceType, typename storedType>
		interfaceType getValue(const Property<interfaceType, storedType> & raw) const;
		Any getValue(const string & rawName) const;

		template<typename interfaceType, typename storedType, typename implicitInterfaceType>
		void setProperty(const Property<interfaceType, storedType> & raw, const implicitInterfaceType & value );

		void setProperty(const string & rawName, const Any & value );	// CAREFUL: THIS DOES NOT INSERT NEW I/O METHODS

	private:
		SharedPointer< Many > propertyValues;

}; // class PropertyContainer

#include <PropertyContainer.tpp>

#endif