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
	if(lhs.is_object() and rhs.is_object())
	{
		json j = lhs;
		j.insert(rhs.begin(), rhs.end());

		return j;
	}
	else
	{
		return json();
	}

}

} // psin