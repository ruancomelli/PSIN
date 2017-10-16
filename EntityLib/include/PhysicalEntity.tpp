#ifndef PHYSICAL_ENTITY_TPP
#define PHYSICAL_ENTITY_TPP

// UtilsLib
#include <NamedType.hpp>
#include <metaprogramming.hpp>

// JSONLib
#include <json.hpp>

namespace psin {

template<typename...Prs>
void from_json(const json& j, PhysicalEntity<Prs...> & p)
{
	using TypeList = typename PhysicalEntity<Prs...>::PropertyList;

	mp::for_each<mp::provide_indices<TypeList>>(
	[&](auto&& i)
	{
		using P = typename mp::get<i, TypeList>::type;
		if(j.count(NamedType<P>::name) > 0)
		{
			p.template property<P>() = j.at(NamedType<P>::name);
		}
	});
}

template<typename...Prs>
void to_json(json& j, const PhysicalEntity<Prs...> & p)
{
	using TypeList = typename PhysicalEntity<Prs...>::PropertyList;

	mp::for_each<mp::provide_indices<TypeList>>(
	[&](auto&& i)
	{
		using P = typename mp::get<i, TypeList>::type;
		if(p.template assigned<P>()) j[NamedType<P>::name] = p.template get<P>();
	});
}

// ----- Constructors -----
template<typename ... PropertyTypes>
PhysicalEntity<PropertyTypes...>::PhysicalEntity()
{}

// template<typename ... PropertyTypes>
// template<typename...Us>
// PhysicalEntity<PropertyTypes...>::PhysicalEntity(const PhysicalEntity<Us...> & other)
// {
// 	static_assert(mp::type_list<PropertyTypes...>::template contains<Us...>, "Cannot construct PhysicalEntity");

// 	(std::get<Us>(this->propertyTuple) = std::get<Us>(other.propertyTuple));...
// }

// ----- Return property -----
template<typename ... PropertyTypes>
template<typename PropertyType>
PropertyType& PhysicalEntity<PropertyTypes...>::property()
{
	static_assert(mp::type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'PhysicalEntity<PropertyTypes...>::property' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple);
}

template<typename ... PropertyTypes>
template<typename PropertyType>
PropertyType PhysicalEntity<PropertyTypes...>::property() const
{
	static_assert(mp::type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'PhysicalEntity<PropertyTypes...>::property' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple);
}

// ----- Set and get property -----
template<typename ... PropertyTypes>
template<typename PropertyType, typename ValueType>
void PhysicalEntity<PropertyTypes...>::set(const ValueType & value)
{
	static_assert(mp::type_list<PropertyTypes...>::template contains<PropertyType>, 
		"Template parameter for function 'PhysicalEntity<PropertyTypes...>::set' must be in template parameter list in the specialization of 'PhysicalEntity'");

	this->template property<PropertyType>().set(value);
}

template<typename ... PropertyTypes>
template<typename PropertyType>
typename PropertyType::ValueType PhysicalEntity<PropertyTypes...>::get() const
{
	static_assert(mp::type_list<PropertyTypes...>::template contains<PropertyType>, 
		"Template parameter for function 'PhysicalEntity<PropertyTypes...>::get' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return this->template property<PropertyType>().get();
}

// ----- Check whether a property was assigned -----
template<typename ... PropertyTypes>
template<typename PropertyType>
bool PhysicalEntity<PropertyTypes...>::assigned() const
{
	static_assert(mp::contains<mp::type_list<PropertyTypes...>, PropertyType>::value, "Template parameter for function 'assigned' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return this->template property<PropertyType>().assigned();
}

} // psin

#endif
