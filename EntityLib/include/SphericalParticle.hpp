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
	// template<typename ... Args>
	// using vector = std::vector<Args...>;
	
	// using ostream = std::ostream;
	// using string = std::string;

	public:
		// SphericalParticle();
		// explicit SphericalParticle(const Particle & base);
		// SphericalParticle(const int order, const int dimension, const int handle = -1);
		
		// // ---- Geometrical Parameters ----
		// void setGeometricParameter(const int geometricParameterIdentifier, const double geometricParameterValue);
		// void setGeometricParameter(const DoubleVector geometricParameterVector);
		// double getGeometricParameter(const int geometricParameterIdentifier) const;
		// DoubleVector getGeometricParameter() const;
		
		// // ---- Collision ----
		// bool touches( const SphericalParticlePtr neighbor ) const;

		// Vector3D contactPoint( const SphericalParticlePtr neighbor ) const;
		// Vector3D normalDirection( const SphericalParticlePtr neighbor ) const;
		// Vector3D relativeTangentialVelocity( const SphericalParticlePtr neighbor ) const;
		// Vector3D tangentialVersor( const SphericalParticlePtr neighbor ) const;

		// double overlap( const SphericalParticlePtr neighbor ) const;
		// double overlapDerivative( const SphericalParticlePtr neighbor ) const;
		
		// // ---- Input and Output ----
		// void fwritePosition( ostream & outFile, const string horizontalSeparator, const string verticalSeparator );

	private:
		// DoubleVector geometricParameter;
		
		// void reserveGeometricParameterMemory(void);
};


template<typename ... Args>
bool touch(const SphericalParticle<Args...> & left, const SphericalParticle<Args...> & right);

template<typename ... Args>
double overlap(const SphericalParticle<Args...> & left, const SphericalParticle<Args...> & right);


#include <SphericalParticle.tpp>

#endif
