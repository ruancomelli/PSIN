#ifndef VALUED_PROPERTY_CONTAINER_H
#define VALUED_PROPERTY_CONTAINER_H

// PropertyLib
#include <PropertyContainer.hpp>

// Standard
#include <functional>
#include <iostream>
#include <map>
#include <string>

// UtilsLib
#include <Any.hpp>


template<typename ... PropertyTypes>
class ValuedPropertyContainer : public PropertyContainer<PropertyTypes...>
{
	using string = std::string;

	public:
		using InputMethodType = std::function< bool(std::ifstream & in, Any & value) >;
		using OutputMethodType = std::function< bool(std::ofstream & in, Any & value) >;

		// ---- Get, add and set properties and values ----
		ValuedPropertyContainer();
		explicit ValuedPropertyContainer( const PropertyContainer<PropertyTypes...> & propertyContainer );

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

}; // class ValuedPropertyContainer



#include <ValuedPropertyContainer.tpp>

#endif // VALUED_PROPERTY_CONTAINER_H
