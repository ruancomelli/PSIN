#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP

// Standard
#include <functional>

// EntityLib
#include <PhysicalEntity.hpp>
#include <SocialEntity.hpp>
#include <SpatialEntity.hpp>

// UtilsLib
#include <Named.hpp>
#include <Vector.hpp>

namespace psin {
	
template<typename ... PropertyTypes>
class Boundary : 
    public Named,
    public PhysicalEntity<PropertyTypes...>,
    public SpatialEntity
{
	using Spatial = vector<Vector3D>;

	public:
		using BasePhysicalEntity = PhysicalEntity<PropertyTypes...>;

		template<typename Time>
		void updatePosition(const Time & t);

		template<typename Time>
		void updateOrientation(const Time & t);
};

} // psin

#include <Boundary.tpp>

#endif
