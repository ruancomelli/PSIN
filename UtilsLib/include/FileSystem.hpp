#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

// boost
#include <boost/filesystem.hpp>

// UtilsLib
#include <string.hpp>

// JSONLib
#include <json.hpp>

namespace psin {

namespace filesystem = boost::filesystem;
using filesystem::path;

bool checkPathExists( const std::string & pathName );

bool createDirectory( const std::string & pathName );

std::string currentDirectory(void);
std::string parentDirectory(const std::string & pathName);

void deletePath( const std::string & pathName );

void from_json(const json & j, path & p);
void to_json(json & j, const path & p);

} // psin

#endif
