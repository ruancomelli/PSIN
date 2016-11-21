#ifndef READ_PHYSICAL_ENTITY_H
#define READ_PHYSICAL_ENTITY_H

// Standard
#include <fstream>
#include <iostream>
#include <string>

// EntityLib
#include <Entity.h>
#include <PhysicalEntity.h>

// IOLib
#include <readEntity.h>
#include <FileReader.h>

using namespace std;

PhysicalEntity readPhysicalEntity( string & fileName );

#endif