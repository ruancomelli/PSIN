#ifndef BOUNDARY_H
#define BOUNDARY_H

// Standard
#include <functional>

// EntityLib
#include <PhysicalEntity.hpp>
#include <SocialEntity.hpp>
#include <SpatialEntity.hpp>

// UtilsLib
#include <SharedPointer.hpp>

template<typename ... PropertyTypes>
class Boundary : 
    public PhysicalEntity<PropertyTypes...>,
    public SocialEntity,
    public SpatialEntity
{
	using Spatial = vector<Vector3D>;

	public:
		void setPositionFunction( const std::function< Spatial(double)> & f );
		void setOrientationFunction( const std::function< Spatial(double)> & f );

		void updatePosition(double t);
		void updateOrientation(double t);
		
	private:
		std::function< Spatial(double)> positionFunction;
		std::function< Spatial(double)> orientationFunction;
};

#include <Boundary.tpp>

#endif
