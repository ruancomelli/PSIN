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
		typedef bool (*inputMethodType)(ifstream & in, boost::any & value);
		typedef bool (*outputMethodType)(ofstream & in, boost::any & value);

		// ---- Get, add and set properties and values ----
		PropertyContainer();

		// Get a property
		template<typename interfaceType, typename storedType>
		Property<interfaceType, storedType> getProperty(const RawProperty<interfaceType, storedType> & raw) const;

		// Get a property's value
		template<typename interfaceType, typename storedType>
		interfaceType getValue(const RawProperty<interfaceType, storedType> & raw) const;

		// Get a property's input method
		template<typename interfaceType, typename storedType>
		inputMethodType getInputMethod(const string & rawName) const;

		// Get a property's output method
		template<typename interfaceType, typename storedType>
		outputMethodType getOutputMethod(const string & rawName) const;

		// Sets or adds a property
		/*template<typename interfaceType, typename storedType>
		void setProperty(const RawProperty<interfaceType, storedType> & raw, const interfaceType & value );*/

		template<typename interfaceType, typename storedType, typename implicitInterfaceType>
		void setProperty(const RawProperty<interfaceType, storedType> & raw, const implicitInterfaceType & value );

		template<typename interfaceType, typename storedType>
		void setProperty(const Property<interfaceType, storedType> & property);

		set<string> getPropertyNames(void);

	private:
		SharedPointer< many > propertyValues;
		SharedPointer< set<string> > propertyNames;
		SharedPointer< std::vector< inputMethodType > > inputMethods;
		SharedPointer< std::vector< outputMethodType > > outputMethods;
}; // class PropertyContainer

#include <PropertyContainer.tpp>

#endif