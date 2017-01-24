#ifndef READ_ENTITY_H
#define READ_ENTITY_H

// Standard
#include <fstream>
#include <iostream>
#include <string>

// EntityLib
#include <Entity.h>
#include <FileReader.h>

using namespace std;

EntityPtr readEntity( const string fileName );

#endif