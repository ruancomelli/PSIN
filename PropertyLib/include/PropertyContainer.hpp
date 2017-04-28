#ifndef PROPERTY_CONTAINER_H
#define PROPERTY_CONTAINER_H

// PropertyLib
#include <Property.hpp>

// UtilsLib
#include <Any.hpp>
#include <TypeIsInList.hpp>
#include <UniqueTypeList.hpp>
#include <Variant.hpp>

// Standard
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <tuple>

template<typename ... PropertyTypes>
class PropertyContainer
{
	static_assert(is_unique_type_list<PropertyTypes...>::value, "Template parameters cannot be repeated in PropertyContainer specialization.");

	public:
		// ---- Get, add and set properties and values ----
		// PropertyContainer();
		// explicit PropertyContainer( const PropertyContainer<PropertyTypes...> & propertyContainer );

		// // Get a property's value
		// template<typename InterfaceType, typename StoredType>
		// InterfaceType getValue(const Property<InterfaceType, StoredType> & property) const;
		// Any getValue(const string & propertyName) const;

		// // Set property - By-property and by-name versions
		// template<typename InterfaceType, typename StoredType, typename implicitInterfaceType>
		// void setProperty(const Property<InterfaceType, StoredType> & property, const implicitInterfaceType & value );
		// 	// Sets a value to the correspondent property. If the property was not inserted yet, it is.

		// void setProperty(const string & propertyName, const Any & value );	// CAREFUL: THIS DOES NOT INSERT NEW I/O METHODS
		// 	// Throws an exception if propertyName was not already inserted.

		// // Check whether a property was set. By-name and by-property versions
		// bool checkSetted(const string & propertyName);
		// template<typename InterfaceType, typename StoredType>
		// bool checkSetted(const Property<InterfaceType, StoredType> & property);



		///////////////////////////// NEW /////////////////////////////

		// Get property
		template<typename PropertyType, typename Ret, typename ... Args>
		Ret call(std::function<Ret(PropertyType &, Args...)> functionToCall, Args ... args);

		template<typename PropertyType, typename Ret, typename ... Args>
		Ret call( Ret (PropertyType::* functionToCall)(Args...), Args ... args);

		// template<typename T>		// MAKE THIS WORK, PLEASE!!!
		// T p = get<T>(property);

	protected:
		std::tuple<PropertyTypes...> property;

}; // class PropertyContainer<PropertyTypes...>

#include <PropertyContainer.tpp>

#endif // PROPERTY_CONTAINER_H

// CRIAR CLASSE has_properties<P...>, da qual as partículas devem DERIVAR (pois elas têm propriedades)
// has_properties<P...> deve ter um dado membro público (ou função) template<Prop> property, que é a propriedade em questão. 

