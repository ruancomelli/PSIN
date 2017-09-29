#ifndef FIXED_BOUNDARY_TPP
#define FIXED_BOUNDARY_TPP

namespace psin {

template<typename ... PropertyTypes>
FixedBoundary<PropertyTypes...>::FixedBoundary(const BaseBoundary & boundary)
	: BaseBoundary(boundary)
{}

template<typename ... PropertyTypes>
FixedBoundary<PropertyTypes...>::FixedBoundary(BaseBoundary && boundary)
	: BaseBoundary(boundary)
{}

template<typename ... PropertyTypes>
template<typename Time>
void FixedBoundary<PropertyTypes...>::update(const Time & time) const
{}


template<typename ... PropertyTypes>
void from_json(const json& j, FixedBoundary<PropertyTypes...> & fixed)
{
	typename FixedBoundary<PropertyTypes...>::BaseBoundary boundary = j;

	fixed = FixedBoundary<PropertyTypes...>(boundary);
}

template<typename ... PropertyTypes>
void to_json(json& j, const FixedBoundary<PropertyTypes...> & fixed)
{
	typename FixedBoundary<PropertyTypes...>::BaseBoundary boundary = fixed;

	j = boundary;
}

} // psin

#endif
