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

// boost
#include <boost/any.hpp>
#include <boost/make_shared.hpp>
using many = std::vector<boost::any>;

using namespace std;

class PropertyContainer : public RawPropertyContainer
{
	public:
		typedef bool (*inputMethodType)(ifstream & in, boost::any & value);
		typedef bool (*outputMethodType)(ofstream & in, boost::any & value);

		// ---- Get, add and set properties and values ----
		PropertyContainer();
		explicit PropertyContainer( const RawPropertyContainer & raw );

		// Get a property
		template<typename interfaceType, typename storedType>
		Property<interfaceType, storedType> getProperty(const RawProperty<interfaceType, storedType> & raw) const;

		// Get a property's value
		template<typename interfaceType, typename storedType>
		interfaceType getValue(const RawProperty<interfaceType, storedType> & raw) const;

		template<typename interfaceType, typename storedType, typename implicitInterfaceType>
		void setProperty(const RawProperty<interfaceType, storedType> & raw, const implicitInterfaceType & value );

		void setProperty(const string & rawName, const boost::any & value );	// CAREFUL: THIS DOES NOT INSERT NEW I/O METHODS

		template<typename interfaceType, typename storedType>
		void setProperty(const Property<interfaceType, storedType> & property);

	private:
		SharedPointer< many > propertyValues;

}; // class PropertyContainer

#include <PropertyContainer.tpp>

#endif