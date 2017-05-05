#ifndef PHYSICAL_ENTITY_HPP
#define PHYSICAL_ENTITY_HPP

// UtilsLib
#include <UniqueTypeList.hpp>

// Standard
#include <iostream>
#include <tuple>

template<typename ... PropertyTypes>
class PhysicalEntity
{
	static_assert(is_unique_type_list<PropertyTypes...>::value, "Template parameters cannot be repeated in 'PhysicalEntity' specialization.");

	public:
		PhysicalEntity();
		PhysicalEntity(const PhysicalEntity<PropertyTypes...> & other);

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

#include <PhysicalEntity.tpp>

#endif
