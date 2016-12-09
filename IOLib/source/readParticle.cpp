#include <readParticle.h>

Particle readParticle( string & fileName )
{
	return Particle(readPhysicalEntity(fileName));
}