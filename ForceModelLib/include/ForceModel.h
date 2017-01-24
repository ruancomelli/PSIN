#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H

// std
#include <cmath>
#include <string>
#include <vector>
#include <ctype.h>
#include <stdexcept>

// UtilsLibSpecific
#include <Vector3D.h>
#include <Vector.h>
#include <Mathematics.h>
#include <SharedPointer.h>

// EntityLib
#include <Entity.h>
#include <PhysicalEntity.h>
#include <Particle.h>
#include <SphericalParticle.h>


class ForceModel
{
	public:	
		static vector<Vector3D> taylorPredictor( const vector<Vector3D> & currentVector, const int predictionOrder, const double dt );
		
		// Force calculation models
		static void viscoelasticSpheres( SphericalParticlePtr particle1, SphericalParticlePtr particle2 );
		static void linearDashpotForce( SphericalParticlePtr particle1, SphericalParticlePtr particle2 );
		
		static void correctPosition( SphericalParticlePtr particle, const int predictionOrder, double dt );
		static void correctOrientation( SphericalParticlePtr particle, const int predictionOrder, double dt );
		
		static vector<Vector3D> gearCorrector(const vector<Vector3D> & predictedVector, const Vector3D & doubleDerivative, const int predictionOrder, const double dt);
	
	private:
};

#endif
