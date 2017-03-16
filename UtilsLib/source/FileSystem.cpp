#include <FileSystem.h>

// boost
#include <boost/filesystem.hpp>

bool checkPathExists( const std::string pathName )
{
	boost::filesystem::path directory(pathName);
	return boost::filesystem::exists( directory );
}

bool createDirectory( const std::string pathName )
{
	boost::filesystem::path directory(pathName);
	return boost::filesystem::create_directories(directory);
}

void deletePath( const std::string pathName )
{
	boost::filesystem::path directory(pathName);
	boost::filesystem::remove_all(directory);
}