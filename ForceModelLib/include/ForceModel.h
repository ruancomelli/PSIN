#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H

#include <cmath>
#include <string>
#include <vector>
#include <ctype.h>
#include <Vector3D.h>
#include <Vector.h>
#include <Entity.h>
#include <PhysicalEntity.h>
#include <Particle.h>
#include <SphericalParticle.h>
#include <stdexcept>

// factorial:
//	Calculates n!, where n is a nonnegative integer
inline unsigned long factorial( unsigned n ){ 
  unsigned long nFactorial = 1;
	
	for( unsigned k = 1 ; k <= n ; ++k )
		nFactorial *= k;
	
	return nFactorial;
}


class ForceModel
{
	public:	
		static vector<Vector3D> taylorPredictor( const vector<Vector3D> currentVector, const int predictionOrder, const double dt );
		
		// Force calculation models
		static void ForceModel::viscoelasticSpheres(SphericalParticle particle1, SphericalParticle particle2, Vector3D normalForce, Vector3D tangentialForce);
		
		//static DoubleVector linearDashpotForce(Particle particle1, Particle particle2, string method, string interaction );
			// This has to be implemented
			
		static vector<Vector3D> gearCorrector(const vector<Vector3D> & predictedVector, const Vector3D & doubleDerivative, const int predictionOrder, const double dt);
	
	private:
};

#endif
