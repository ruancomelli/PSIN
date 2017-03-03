#include <CreateDirectory.h>

// boost
#include <boost/filesystem.hpp>

void createDirectory( const string & pathName )
{
	boost::filesystem::path directory(pathName);
	boost::filesystem::create_directory(directory);
}