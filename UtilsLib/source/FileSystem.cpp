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

void from_json(const json & j, path & p)
{
	p = path(j.get<string>());
}

void to_json(json & j, const path & p)
{
	j = json(p.string());
}

} // psin

namespace nlohmann {

void adl_serializer<psin::path>::from_json(const json & j, psin::path & p)
{
	p = psin::path(j.get<psin::string>());
}

void adl_serializer<psin::path>::to_json(json & j, const psin::path & p)
{
	j = json(p.string());
}

} // nlohmann