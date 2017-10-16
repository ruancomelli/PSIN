#ifndef PHYSICAL_ENTITY_HPP
#define PHYSICAL_ENTITY_HPP

// UtilsLib
#include <mp/bool_constant.hpp>
#include <mp/logical.hpp>
#include <mp/type_collection.hpp>

// JSONLib
#include <json.hpp>

// Standard
#include <tuple>
#include <type_traits>

namespace psin {

template<typename ... PropertyTypes>
class PhysicalEntity
{
	template<typename...Us>
	friend class PhysicalEntity;

	public:
		using PropertyList = mp::type_collection<PropertyTypes...>;

		template<typename Pr>
		struct has_property : mp::bool_constant< PropertyList::template contains<Pr> >
		{};

		PhysicalEntity();

		// template<typename...Us>
		// PhysicalEntity(const PhysicalEntity<Us...> & other);

		// ----- Return property -----
		template<typename PropertyType>
		PropertyType& property();

		template<typename PropertyType>
		PropertyType property() const;

		// ----- Set and get property -----
		template<typename PropertyType, typename ValueType>
		void set(const ValueType & value);

		template<typename PropertyType>
		typename PropertyType::ValueType get() const;

		// ----- Check whether a property was assigned -----
		template<typename PropertyType>
		bool assigned() const;

	protected:
		typename mp::type_collection<PropertyTypes...>::template specialize<std::tuple> propertyTuple;
};

// General case
template<typename Entity, typename PropertyType, typename SFINAE = void>
struct has_property
	: mp::contains<typename Entity::PropertyList, PropertyType>
{};

// In case Entity has a member metafunction has_property, use it to evaluate psin::has_property
// In this case, has_property<Entity, PropertyType>::value iff Entity::has_property<PropertyType>::value
template<typename Entity, typename PropertyType>
struct has_property<
		Entity, 
		PropertyType,
		typename std::enable_if<
			Entity::template has_property<PropertyType>::value
		>::type
	>
	: std::true_type
{};

template<typename Entity, typename...Ps>
struct has_properties
	: mp::conjunction<
		has_property<Entity, Ps>...
	>
{};

template<typename...Prs>
void from_json(const json& j, PhysicalEntity<Prs...> & p);
template<typename...Prs>
void to_json(json& j, const PhysicalEntity<Prs...> & p);

} // psin

#include <PhysicalEntity.tpp>

#endif
