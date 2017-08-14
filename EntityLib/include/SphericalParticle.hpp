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
		template<typename...Us>
		Vector3D relativeTangentialVelocity(const SphericalParticle<Us...> & neighbor) const;
		
		template<typename...Us>
		Vector3D tangentialVersor(const SphericalParticle<Us...> & neighbor) const;
};


template<typename...Ts, typename...Us>
bool touch(const SphericalParticle<Ts...> & left, const SphericalParticle<Us...> & right);

template<typename...Ts, typename...Us>
double overlap(const SphericalParticle<Ts...> & left, const SphericalParticle<Us...> & right);

template<typename...Ts, typename...Us>
double overlapDerivative(const SphericalParticle<Ts...> & left, const SphericalParticle<Us...> & right);

template<typename...Ts, typename...Us>
Vector3D contactPoint(const SphericalParticle<Ts...> & left, const SphericalParticle<Us...> & right);

template<typename T>
struct is_spherical;

template<typename...Ts>
struct is_spherical< SphericalParticle<Ts...> > : std::true_type {};

#include <SphericalParticle.tpp>

#endif
