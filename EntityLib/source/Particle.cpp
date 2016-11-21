#include <Particle.h>

Particle::Particle() : PhysicalEntity(3, 3) 
{
	
}

Particle::Particle( const PhysicalEntity & base )
	: PhysicalEntity( base )
{

}

Particle::Particle(const int taylorOrder, const int dimension, const int handle)
	: PhysicalEntity(taylorOrder, dimension, handle)
{
	
}

//Particle::Particle(const int taylorOrder, const int handle)
//{
//	setTaylorOrder(taylorOrder); //It also allocs memory to orientation and position vectors.
//}