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
	static vector < vector <double> > taylorPredictor( vector < vector <double> > currentVector, unsigned predictionOrder, double dt );
	static vector <double> linearDashpotForce(Particle particle1, Particle particle2);
};

#endif
