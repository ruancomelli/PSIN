#include <FileSystem.hpp>

// boost
#include <boost/filesystem.hpp>

namespace psin {

bool checkPathExists( const std::string & pathName )
{
	boost::filesystem::path directory(pathName);
	return boost::filesystem::exists( directory );
}

bool createDirectory( const std::string & pathName )
{
	boost::filesystem::path directory(pathName);
	return boost::filesystem::create_directories(directory);
}

std::string currentDirectory(void)
{
	return boost::filesystem::current_path().string();
}

std::string parentDirectory(const std::string & pathName)
{
	boost::filesystem::path directory(pathName);
	return directory.parent_path().string();
}

void deletePath( const std::string & pathName )
{
	boost::filesystem::path directory(pathName);
	boost::filesystem::remove_all(directory);
}

} // psin