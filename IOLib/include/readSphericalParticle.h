#ifndef READ_SPHERICAL_PARTICLE_H
#define READ_SPHERICAL_PARTICLE_H

// Standard
#include <fstream>
#include <iostream>
#include <string>

// EntityLib
#include <Entity.h>
#include <PhysicalEntity.h>
#include <Particle.h>
#include <SphericalParticle.h>

// IOLib
#include <readEntity.h>
#include <readPhysicalEntity.h>
#include <readParticle.h>
#include <FileReader.h>

using namespace std;

SphericalParticlePtr readSphericalParticle( string & fileName );

#endif