#ifndef SPHERICAL_PARTICLE_H
#define SPHERICAL_PARTICLE_H

#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>
#include <string>

#include <Particle.h>

using namespace std;

enum SphericalParticleGeometricParameter{
	RADIUS = 0,
	N_GEOMETRIC_PARAMETER
};

class SphericalParticle;
typedef SharedPointer< SphericalParticle > SphericalParticlePtr;
typedef vector< SphericalParticle > SphericalParticleArray;
typedef vector< SphericalParticlePtr > SphericalParticlePtrArray;

class SphericalParticle: public Particle
{
	public:
		SphericalParticle();
		explicit SphericalParticle(const Particle & base);
		SphericalParticle(const int order, const int dimension, const int handle = -1);
		
		// ---- Geometrical Parameters ----
		void setGeometricParameter(const int geometricParameterIdentifier, const double geometricParameterValue);
		void setGeometricParameter(const DoubleVector geometricParameterVector);
		double getGeometricParameter(const int geometricParameterIdentifier) const;
		DoubleVector getGeometricParameter() const;
		
		// ---- Collision ----
		inline bool touches( const SphericalParticlePtr neighbor ) const;

		Vector3D contactPoint( const SphericalParticlePtr neighbor ) const;
		Vector3D normalDirection( const SphericalParticlePtr neighbor ) const;
		Vector3D relativeTangentialVelocity( const SphericalParticlePtr neighbor ) const;
		Vector3D tangentialVersor( const SphericalParticlePtr neighbor ) const;

		double overlap( const SphericalParticlePtr neighbor ) const;
		double overlapDerivative( const SphericalParticlePtr neighbor ) const;
		
		// ---- Input and Output ----
		void fwritePosition( ostream & outFile, const string horizontalSeparator, const string verticalSeparator );
		
		// ---- Distance ----
		double distance( const SphericalParticlePtr neighbor) const;


	private:
		DoubleVector geometricParameter;
		
		void reserveGeometricParameterMemory(void);
}; // class SphericalParticle

#endif
