#include <json.hpp>

// Standard
#include <fstream>

namespace psin {
	
json read_json(const std::string & filename)
{
	json j;
	std::ifstream in(filename);
	in >> j;

	return j;
}

} // psin