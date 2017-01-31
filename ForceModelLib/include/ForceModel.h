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
		static Vector3D normalForceViscoelasticSpheres( SphericalParticlePtr particle, SphericalParticlePtr neighbor );
		static Vector3D normalForceLinearDashpotForce( SphericalParticlePtr particle, SphericalParticlePtr neighbor );

		static void tangentialForceHaffWerner( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep );
		static void tangentialForceCundallStrack( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep );
		
		static void correctPosition( SphericalParticlePtr particle, const int predictionOrder, double dt );
		static void correctOrientation( SphericalParticlePtr particle, const int predictionOrder, double dt );
		
		static vector<Vector3D> gearCorrector(const vector<Vector3D> & predictedVector, const Vector3D & doubleDerivative, const int predictionOrder, const double dt);
	
		static bool checkCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor );
		static void startCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor );
		static void endCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor );

		static void setNumberOfParticles( const int numberOfParticles );

		static void addZeta( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor, const Vector3D zeta );
		static void setZeta( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor, const Vector3D zeta );
		
	private:
		static void resizeCummulativeZeta( const int numberOfParticles );
		static void resizeCollisionFlag( const int numberOfParticles );

		static vector< vector< Vector3D > > cummulativeZeta;
		static vector< vector< bool > > collisionFlag;

};

#endif
