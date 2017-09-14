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
    if (not (lhs.is_object() and rhs.is_object()))
    {
        JSON_THROW(type_error::create(305, "cannot use merge with " + type_name()));
    }

    json j;

	j.insert(lhs.begin(), lhs.end());
	j.insert(rhs.begin(), rhs.end());

	return j;
}

} // psin