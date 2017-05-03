#ifndef PROPERTY_CONTAINER_HPP
#define PROPERTY_CONTAINER_HPP

// UtilsLib
#include <UniqueTypeList.hpp>

// Standard
#include <iostream>
#include <tuple>

template<typename ... PropertyTypes>
class PropertyContainer
{
	static_assert(is_unique_type_list<PropertyTypes...>::value, "Template parameters cannot be repeated in PropertyContainer specialization.");

	public:
		// ----- Return property -----
		template<typename PropertyType>
		PropertyType& property();

		template<typename PropertyType>
		PropertyType property() const;

		// ----- Input and output property -----
		template<typename PropertyType>
		bool input(std::istream & in);

		template<typename PropertyType>
		bool output(std::ostream & out) const;

		// Check whether a property was assigned
		template<typename PropertyType>
		bool assigned() const;

	protected:
		std::tuple<PropertyTypes...> propertyTuple;
};

#include <PropertyContainer.tpp>

#endif
