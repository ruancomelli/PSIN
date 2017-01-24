#include <readParticle.h>

ParticlePtr readParticle( const string fileName )
{
	return ParticlePtr( new Particle(*readPhysicalEntity(fileName) ) ) ;
}