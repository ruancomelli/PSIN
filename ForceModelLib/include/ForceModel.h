#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H

// std
#include <cmath>
#include <string>
#include <vector>
#include <ctype.h>
#include <stdexcept>

// our code
#include <Vector3D.h>
#include <Vector.h>
#include <Entity.h>
#include <Mathematics.h>
#include <PhysicalEntity.h>
#include <Particle.h>
#include <SphericalParticle.h>


class ForceModel
{
	public:	
		static vector<Vector3D> taylorPredictor( const vector<Vector3D> & currentVector, const int predictionOrder, const double dt );
		
		// Force calculation models
		static void viscoelasticSpheres( SphericalParticle & particle1, SphericalParticle & particle2 );
		static void linearDashpotForce( SphericalParticle & particle1, SphericalParticle & particle2 );
		
		static void correctPosition( SphericalParticle & particle, const int predictionOrder, double dt );
		static void correctOrientation( SphericalParticle & particle, const int predictionOrder, double dt );
		
		static vector<Vector3D> gearCorrector(const vector<Vector3D> & predictedVector, const Vector3D & doubleDerivative, const int predictionOrder, const double dt);
	
	private:
};

#endif
