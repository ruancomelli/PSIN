#ifndef CREATE_DIRECTORY_H
#define CREATE_DIRECTORY_H

// Standard
#include <string>

bool checkPathExists( const std::string pathName );

void createDirectory( const std::string pathName );

void deletePath( const std::string pathName );

#endif