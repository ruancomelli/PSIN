#ifndef PHYSICAL_ENTITY_HPP
#define PHYSICAL_ENTITY_HPP

// UtilsLib
#include <Metaprogramming/type_collection.hpp>

// Standard
#include <tuple>

template<typename ... PropertyTypes>
class PhysicalEntityModel
{
	static_assert(!type_list<PropertyTypes...>::has_repeated_types, "Template parameters cannot be repeated in 'PhysicalEntity' specialization.");

	public:
		using PropertyList = type_collection<PropertyTypes...>;

		PhysicalEntityModel();
		PhysicalEntityModel(const PhysicalEntityModel<PropertyTypes...> & other);

		// ----- Return property -----
		template<typename PropertyType>
		PropertyType& property();

		template<typename PropertyType>
		PropertyType property() const;

		// ----- Input and output property -----
		template<typename PropertyType, typename istream_type>
		bool input(istream_type & in);

		template<typename PropertyType, typename ostream_type>
		bool output(ostream_type & out) const;

		// ----- Set and get property -----
		template<typename PropertyType, typename ValueType>
		void set(const ValueType & value);

		template<typename PropertyType>
		typename PropertyType::ValueType get() const;

		// ----- Check whether a property was assigned -----
		template<typename PropertyType>
		bool assigned() const;

	protected:
		std::tuple<PropertyTypes...> propertyTuple;
};

template <typename...Ts>
using PhysicalEntity = typename type_collection<Ts...>::template specialize<PhysicalEntityModel>;

#include <PhysicalEntity.tpp>

#endif
