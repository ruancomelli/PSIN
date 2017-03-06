#include <CreateDirectory.h>

// boost
#include <boost/filesystem.hpp>

void createDirectory( const std::string & pathName )
{
	boost::filesystem::path directory(pathName);
	boost::filesystem::create_directory(directory);
}