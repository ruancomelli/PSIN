#ifndef BOUNDARY_TPP
#define BOUNDARY_TPP

namespace psin {

template<typename ... PropertyTypes>
Boundary<PropertyTypes...>::Boundary(const Named & named, const BasePhysicalEntity & physical)
	: Named(named),
	BasePhysicalEntity(physical)
{}

template<typename ... PropertyTypes>
Boundary<PropertyTypes...>::Boundary(Named&& named, BasePhysicalEntity&& physical)
	: Named(named),
	BasePhysicalEntity(physical)
{}


template<typename ... PropertyTypes>
void from_json(const json& j, Boundary<PropertyTypes...> & b)
{
	Named named = j;
	typename Boundary<PropertyTypes...>::BasePhysicalEntity physical = j;

	b = Boundary<PropertyTypes...>(named, physical);
}

template<typename ... PropertyTypes>
void to_json(json& j, const Boundary<PropertyTypes...> & b)
{
	Named named = b;
	typename Boundary<PropertyTypes...>::BasePhysicalEntity physical = b;

	json jn = named;
	json jph = physical;

	j = merge(jn, jph);
}

} // psin

#endif