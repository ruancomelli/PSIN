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

json merge(const json & lhs, const json & rhs)
{
    json j;

	j.insert(lhs.begin(), lhs.end());
	j.insert(rhs.begin(), rhs.end());

	return j;
}

} // psin