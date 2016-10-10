#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H

#include <cmath>
#include <string>
#include <vector>
#include <ctype.h>

#include "Vector.h"
#include "Particle.h"

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
		static DoubleVector2D taylorPredictor( DoubleVector2D currentVector, int predictionOrder, double dt );
		//static DoubleVector linearDashpotForce(Particle particle1, Particle particle2, string method, string interaction );
		static DoubleVector2D gearCorrector(const DoubleVector2D & predictedVector, const DoubleVector & doubleDerivative, int predictionOrder, double dt);

};

#endif