#include <Particle.h>

Particle::Particle() : PhysicalEntity(2, 3) {
	
}

Particle::Particle(const int taylorOrder, const int dimension, const int handle)
	: PhysicalEntity(taylorOrder, dimension, handle)
{
	
}