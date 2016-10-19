#include <Particle.h>

Particle::Particle() : PhysicalEntity(2, 3) 
{
	this->resultingForceDV.resize(3);
}

Particle::Particle(const int taylorOrder, const int dimension, const int handle)
	: PhysicalEntity(taylorOrder, dimension, handle)
{
	this->resultingForceDV.resize(dimension);
}

//Particle::Particle(const int taylorOrder, const int handle)
//{
//	setTaylorOrder(taylorOrder); //It also allocs memory to orientation and position vectors.
//}