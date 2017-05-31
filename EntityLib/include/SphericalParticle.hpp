#ifndef SPHERICAL_PARTICLE_HPP
#define SPHERICAL_PARTICLE_HPP

// Standard
#include <ostream>
#include <vector>
#include <string>

// EntityLib
#include <Particle.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// UtilsLib
#include <Vector.hpp>

template<typename ... PropertyTypes>
class SphericalParticle : public Particle<PropertyDefinitions::Radius, PropertyTypes...>
{
	using BaseParticle = Particle<PropertyDefinitions::Radius, PropertyTypes...>;

	public:
		SphericalParticle();
		explicit SphericalParticle(const BaseParticle & base);
		explicit SphericalParticle(const int handle, const int taylorOrder = DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
		
		// ---- Collision ----
		Vector3D relativeTangentialVelocity(const SphericalParticle<PropertyTypes...> & neighbor) const;
		Vector3D tangentialVersor(const SphericalParticle<PropertyTypes...> & neighbor) const;
};


template<typename ... Args>
bool touch(const SphericalParticle<Args...> & left, const SphericalParticle<Args...> & right);

template<typename ... Args>
double overlap(const SphericalParticle<Args...> & left, const SphericalParticle<Args...> & right);

template<typename ... Args>
double overlapDerivative(const SphericalParticle<Args...> & left, const SphericalParticle<Args...> & right);

template<typename ... Args>
Vector3D contactPoint(const SphericalParticle<Args...> & left, const SphericalParticle<Args...> & right);


#include <SphericalParticle.tpp>

#endif
