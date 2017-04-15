#ifndef PROPERTY_CONTAINER_H
#define PROPERTY_CONTAINER_H

// PropertyLib
#include <RawPropertyContainer.hpp>

// Standard
#include <functional>
#include <iostream>
#include <map>
#include <string>

// UtilsLib
#include <Any.hpp>

using std::string;

class PropertyContainer : public RawPropertyContainer
{
	public:
		using InputMethodType = std::function< bool(std::ifstream & in, Any & value) >;
		using OutputMethodType = std::function< bool(std::ofstream & in, Any & value) >;

		// ---- Get, add and set properties and values ----
		PropertyContainer();
		explicit PropertyContainer( const RawPropertyContainer & raw );

		// Get a property's value
		template<typename InterfaceType, typename StoredType>
		InterfaceType getValue(const Property<InterfaceType, StoredType> & property) const;
		Any getValue(const string & propertyName) const;

		// Set property - By-property and by-name versions
		template<typename InterfaceType, typename StoredType, typename implicitInterfaceType>
		void setProperty(const Property<InterfaceType, StoredType> & property, const implicitInterfaceType & value );
			// Sets a value to the correspondent property. If the property was not inserted yet, it is.

		void setProperty(const string & propertyName, const Any & value );	// CAREFUL: THIS DOES NOT INSERT NEW I/O METHODS
			// Throws an exception if propertyName was not already inserted.

		// Check whether a property was set. By-name and by-property versions
		bool checkSetted(const string & propertyName);
		template<typename InterfaceType, typename StoredType>
		bool checkSetted(const Property<InterfaceType, StoredType> & property);

	private:
		SharedPointer< std::map<string, Any> > propertyValues;
		SharedPointer< std::map<string, bool> > settedFlag; // asserts whether each value was set

}; // class PropertyContainer

#include <PropertyContainer.tpp>

#endif
