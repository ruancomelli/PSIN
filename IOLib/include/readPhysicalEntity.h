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

// PropertyLib
#include <PropertyContainer.h>
#include <PropertyList.h>

using namespace std;
using namespace PropertyList;

PhysicalEntityPtr readPhysicalEntity( const string fileName );

#endif