#ifndef FORCE_MODEL_H
#define FORCE_MODEL_H

#include <cmath>
#include <string>
#include <vector>

#include "Vector.h"
#include "Particle.h"

unsigned long factorial( unsigned n );

class ForceModel
{
	static vector < vector <double> > taylorPredictor( vector < vector <double> > currentVector, unsigned predictionOrder, double dt );
	static vector <double> linearDashpotForce(Particle particle1, Particle particle2);
};

#endif
