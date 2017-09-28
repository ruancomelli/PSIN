#ifndef FIXED_BOUNDARY_HPP
#define FIXED_BOUNDARY_HPP

// EntityLib
#include <Boundary.hpp>

namespace psin {

template<typename ... PropertyTypes>
class FixedBoundary : 
    public Boundary<PropertyTypes...>
{
	using BaseBoundary = Boundary<PropertyTypes...>;
	using Spatial = vector<Vector3D>;

	public:
		explicit FixedBoundary(const Vector3D & position = Vector3D(), const Vector3D & orientation = Vector3D());

		template<typename Time>
		void updatePosition(const Time & t) const;

		template<typename Time>
		void updateOrientation(const Time & t) const;
};

} // psin

#include <FixedBoundary.tpp>

#endif
