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

using namespace std;

void addZeta( vector< vector< Vector3D > > & cummulativeZeta, const SphericalParticlePtr particle, const SphericalParticlePtr neighbor, const Vector3D zeta );
void setZeta( vector< vector< Vector3D > > & cummulativeZeta, const SphericalParticlePtr particle, const SphericalParticlePtr neighbor, const Vector3D zeta );
void resizeCummulativeZeta( vector< vector< Vector3D > > & cummulativeZeta, const int numberOfParticles );

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

		static void setNumberOfParticles( const int nParticles ); // TO-DO: undo static!!

/*		string getName(void){ return this->name; }
		void setName(string name){ this->name = name; }*/
		
	private:
		static void resizeCollisionFlag( const int nParticles );

		static vector< vector< bool > > collisionFlag;

		static int numberOfParticles; // TO-DO: undo static!!
		/*string name;*/

};

#endif
