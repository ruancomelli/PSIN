#ifndef PHYSICAL_ENTITY_HPP
#define PHYSICAL_ENTITY_HPP

// UtilsLib
#include <is_unique_type_list.hpp>
#include <specialize_from_unique_list.hpp>

// Standard
#include <iostream>
#include <tuple>

template<typename ... PropertyTypes>
class PhysicalEntityModel
{
	static_assert(is_unique_type_list<PropertyTypes...>::value, "Template parameters cannot be repeated in 'PhysicalEntity' specialization.");

	public:
		PhysicalEntityModel();
		PhysicalEntityModel(const PhysicalEntityModel<PropertyTypes...> & other);

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

template <typename...Ts>
using PhysicalEntity = typename specialize_from_unique_list<PhysicalEntityModel, Ts...>::value;

#include <PhysicalEntity.tpp>

#endif
