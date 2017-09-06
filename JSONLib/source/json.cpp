#include <json.hpp>

// Standard
#include <fstream>

json read_json(const std::string & filename)
{
	json j;
	std::ifstream in(filename);
	in >> j;

	return j;
}