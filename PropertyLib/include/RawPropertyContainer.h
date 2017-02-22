#ifndef RAW_PROPERTY_CONTAINER_H
#define RAW_PROPERTY_CONTAINER_H

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

class RawPropertyContainer
{
	public:
		typedef bool (*inputMethodType)(ifstream & in, boost::any & value);
		typedef bool (*outputMethodType)(ofstream & in, boost::any & value);

		// ---- Get, add and set properties and values ----
		RawPropertyContainer();
		RawPropertyContainer( const RawPropertyContainer & other);

		// Get a property's input method
		inputMethodType getInputMethod(const string & rawName) const;

		// Get a property's output method
		outputMethodType getOutputMethod(const string & rawName) const;

		template<typename interfaceType, typename storedType>
		void addProperty(const RawProperty<interfaceType, storedType> & raw );

		SharedPointer<set<string>> getPropertyNames(void) const;

	protected:
		SharedPointer< set<string> > propertyNames;
		SharedPointer< std::vector< inputMethodType > > inputMethods;
		SharedPointer< std::vector< outputMethodType > > outputMethods;
}; // class RawPropertyContainer

#include <RawPropertyContainer.tpp>

#endif