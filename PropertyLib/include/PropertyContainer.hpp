#ifndef PROPERTY_CONTAINER_H
#define PROPERTY_CONTAINER_H

// PropertyLib
#include <Property.hpp>

// UtilsLib
#include <Any.hpp>
#include <Variant.hpp>

// Standard
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <set>

template<typename ... PropertyTypes>
class PropertyContainer
{
	using string = std::string;

	public:
		// typename std::function< bool(std::ifstream & in, Any & value) > InputMethodType;
		using InputMethodType = std::function< bool(std::ifstream & in, Any & value) >;
		using OutputMethodType = std::function< bool(std::ofstream & in, Any & value) >;

		// ---- Get, add and set properties and values ----
		PropertyContainer();
		PropertyContainer( const PropertyContainer & other);

		// Get a property's input method
		InputMethodType getInputMethod(const string & name) const;

		// Get a property's output method
		OutputMethodType getOutputMethod(const string & name) const;

		// template<typename InterfaceType, typename StoredType>
		// void insertProperty(const Property<InterfaceType, StoredType> & property );
		template<typename Property>
		void insertProperty(void);

		SharedPointer< std::set<string> > getPropertyNames(void) const;

	protected:
		std::map< string, Variant<PropertyTypes...> > propertyMap; 

		SharedPointer< std::set<string> > propertyNames;
		SharedPointer< std::map< string, InputMethodType > > inputMethods;
		SharedPointer< std::map< string, OutputMethodType > > outputMethods;
}; // class PropertyContainer

#include <PropertyContainer.tpp>

#endif // PROPERTY_CONTAINER_H
