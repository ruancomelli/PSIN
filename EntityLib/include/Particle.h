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
		Particle(const int order, const int dimension, const int handle = -1);
		
	private:
		//DoubleVector2D interactionForce;
			// interaction force between this particle and all other particles and boundaries
}; // class Particle

#endif
