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
	json result = lhs.flatten();
	json tmp = rhs.flatten();

	for ( auto it = tmp.begin(); it != tmp.end(); ++it )
	{
		result[it.key()] = it.value();
	}

	return result.unflatten();
}

} // psin