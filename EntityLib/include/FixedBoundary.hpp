#ifndef FIXED_BOUNDARY_HPP
#define FIXED_BOUNDARY_HPP

// EntityLib
#include <Boundary.hpp>

template<typename ... PropertyTypes>
class FixedBoundary : 
    public Boundary<PropertyTypes...>
{
	using BaseBoundary = Boundary<PropertyTypes...>;
	using Spatial = vector<Vector3D>;

	public:
		explicit FixedBoundary(const Vector3D & position = Vector3D(), const Vector3D & orientation = Vector3D());

		virtual void updatePosition(const double & t);
		virtual void updateOrientation(const double & t);

	private:
		using BaseBoundary::setPositionFunction;
		using BaseBoundary::setOrientationFunction;
};

#include <FixedBoundary.tpp>

#endif
