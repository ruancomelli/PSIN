#ifndef FIXED_BOUNDARY_HPP
#define FIXED_BOUNDARY_HPP

// EntityLib
#include <Boundary.hpp>

namespace psin {

template<typename ... PropertyTypes>
class FixedBoundary : 
    public Boundary<PropertyTypes...>
{
	public:
		using BaseBoundary = Boundary<PropertyTypes...>;
		
		FixedBoundary() = default;
		FixedBoundary(const BaseBoundary & boundary);
		FixedBoundary(BaseBoundary && boundary);

		template<typename Time>
		void update(const Time & t) const;
};

template<typename ... PropertyTypes>
void from_json(const json& j, FixedBoundary<PropertyTypes...> & fixed);
template<typename ... PropertyTypes>
void to_json(json& j, const FixedBoundary<PropertyTypes...> & fixed);

} // psin

#include <FixedBoundary.tpp>

#endif
