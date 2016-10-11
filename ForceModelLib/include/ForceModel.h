#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H

#include <cmath>
#include <string>
#include <vector>
#include <ctype.h>

#include <Vector.h>
#include <Particle.h>

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
		//static DoubleVector linearDashpotForce(Particle particle1, Particle particle2, string method, string interaction );
		static DoubleVector2D gearCorrector(const DoubleVector2D & predictedVector, const DoubleVector & doubleDerivative, int predictionOrder, double dt);

	private:
};

#endif