#ifndef READ_PARTICLE_H
#define READ_PARTICLE_H

// Standard
#include <fstream>
#include <iostream>
#include <string>

// EntityLib
#include <Entity.h>
#include <PhysicalEntity.h>
#include <Particle.h>

// IOLib
#include <readEntity.h>
#include <readPhysicalEntity.h>
#include <FileReader.h>

using namespace std;

Particle readParticle( string & fileName );

#endif