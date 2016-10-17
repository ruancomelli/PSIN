#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>

#include <PhysicalEntity.h>

using namespace std;

class Particle: public PhysicalEntity
{
	public:
		Particle();
		Particle(const int taylorOrder, const int dimension, const int handle = -1);
		
		void addForce(DoubleVector force){ this->resultingForce += force; }
		void setResultingForce(DoubleVector force){ this->resultingForce = force; }
		DoubleVector getResultingForce(void){ return this->resultingForce; }
		
	private:
		DoubleVector resultingForce;
		//DoubleVector2D interactionForce;
			// interaction force between this particle and all other particles and boundaries
}; // class Particle

#endif
