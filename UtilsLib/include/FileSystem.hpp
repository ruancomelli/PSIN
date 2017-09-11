#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

// UtilsLib
#include <string.hpp>

namespace psin {

bool checkPathExists( const std::string & pathName );

bool createDirectory( const std::string & pathName );

std::string currentDirectory(void);
std::string parentDirectory(const std::string & pathName);

void deletePath( const std::string & pathName );

} // psin

#endif
