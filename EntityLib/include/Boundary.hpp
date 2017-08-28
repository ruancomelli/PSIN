#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP

// Standard
#include <functional>

// EntityLib
#include <PhysicalEntity.hpp>
#include <SocialEntity.hpp>
#include <SpatialEntity.hpp>

namespace psin {
	
template<typename ... PropertyTypes>
class Boundary : 
    public PhysicalEntity<PropertyTypes...>,
    public SocialEntity,
    public SpatialEntity
{
	using Spatial = vector<Vector3D>;

	public:
		virtual void setPositionFunction( const std::function< Spatial(double)> & f );
		virtual void setOrientationFunction( const std::function< Spatial(double)> & f );

		virtual void updatePosition(const double & t);
		virtual void updateOrientation(const double & t);
		
	private:
		std::function< Spatial(double)> positionFunction;
		std::function< Spatial(double)> orientationFunction;
};

} // psin

#include <Boundary.tpp>

#endif
