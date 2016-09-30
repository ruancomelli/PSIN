#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>

#include "PhysicalEntity.h"

using namespace std;

class Particle: public PhysicalEntity
{
	// index
	public:
		long unsigned getIndex(void);
		void setIndex(long unsigned);
		
	private:
		DoubleVector2D interactionForce;
			// interaction force between this particle and all other particles and boundaries
		long unsigned index;
}; // class Particle

#endif
