#ifndef PROPERTY_CONTAINER_H
#define PROPERTY_CONTAINER_H

// PropertyLib
#include <Property.h>

// Standard
#include <iostream>
#include <string>
#include <set>
#include <list>
#include <vector>

// boost
#include <boost/any.hpp>
#include <boost/make_shared.hpp>
using many = std::vector<boost::any>;

using namespace std;

class PropertyContainer
{
	public:

		// ---- Get, add and set properties and values ----
		PropertyContainer();

		// Get a property
		template<typename interfaceType, typename storedType>
		Property<interfaceType, storedType> getProperty(const RawProperty<interfaceType, storedType> & raw) const;

		// Get a property's value
		template<typename interfaceType, typename storedType>
		interfaceType getValue(const RawProperty<interfaceType, storedType> & raw) const;

		// Sets or adds a property
		/*template<typename interfaceType, typename storedType>
		void setProperty(const RawProperty<interfaceType, storedType> & raw, const interfaceType & value );*/

		template<typename interfaceType, typename storedType, typename implicitInterfaceType>
		void setProperty(const RawProperty<interfaceType, storedType> & raw, const implicitInterfaceType & value );

		template<typename interfaceType, typename storedType>
		void setProperty(const Property<interfaceType, storedType> & property);

	private:
		SharedPointer< many > propertyValues;
		SharedPointer< set<string> > propertyNames;
}; // class PropertyContainer

#include <PropertyContainer.tpp>

#endif