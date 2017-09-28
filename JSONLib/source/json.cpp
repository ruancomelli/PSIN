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
		json result = lhs;

		for ( auto it = rhs.begin(); it != rhs.end(); ++it )
		{
			if(lhs.count(it.key()) > 0)
			{
				result[it.key()] = merge(lhs[it.key()], it.value());
			}
			else
			{
				result[it.key()] = it.value();
			}
		}

		return result;
	}
	else if(lhs.is_array() and rhs.is_array())
	{
		json result = lhs;

		result.insert(result.end(), rhs.begin(), rhs.end());

		return result;
	}
	else if(lhs.is_null())
	{
		return rhs;
	}
	else if(rhs.is_null())
	{
		return lhs;
	}
}

} // psin