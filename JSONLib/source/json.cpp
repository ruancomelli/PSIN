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
	if(lhs.is_object())
	{
		json result = lhs.flatten();
		json tmp = rhs.flatten();

		for ( auto it = tmp.begin(); it != tmp.end(); ++it )
		{
			result[it.key()] = it.value();
		}

		return result.unflatten();
	}
	else if(lhs.is_null())
	{
		return rhs;
	}
}

} // psin