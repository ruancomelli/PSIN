#ifndef PHYSICAL_ENTITY_HPP
#define PHYSICAL_ENTITY_HPP

// UtilsLib
#include <MP/bool_type.hpp>
#include <MP/name.hpp>
#include <MP/type_collection.hpp>

// Standard
#include <tuple>
#include <type_traits>

template<typename ... PropertyTypes>
class PhysicalEntity
{
	template<typename...Us>
	friend class PhysicalEntity;

	public:
		using PropertyList = type_collection<PropertyTypes...>;

		template<typename Pr>
		struct has_property : bool_type< PropertyList::template contains<Pr> >
		{};

		PhysicalEntity();

		// template<typename...Us>
		// PhysicalEntity(const PhysicalEntity<Us...> & other);

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
		typename type_collection<PropertyTypes...>::template specialize<std::tuple> propertyTuple;
};


template<typename...Ts>
struct name< PhysicalEntity<Ts...> >;

template<typename...Ts>
const std::string name< PhysicalEntity<Ts...> >::value = "PhysicalEntity";

#include <PhysicalEntity.tpp>

#endif
