#ifndef CREATE_DIRECTORY_H
#define CREATE_DIRECTORY_H

// Standard
#include <string>

bool checkPathExists( const std::string pathName );

bool createDirectory( const std::string pathName );

std::string currentDirectory(void);
std::string parentDirectory(const std::string pathName);

void deletePath( const std::string pathName );

#endif