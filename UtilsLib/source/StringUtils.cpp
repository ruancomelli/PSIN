#include <StringUtils.hpp>

// Standard
#include <algorithm>

namespace psin {

// Compare strings case sensitive or not
int stringCompare( std::string left, std::string right, const bool caseSensitive )
{
	if(!caseSensitive)
	{
		for(auto& c : left) c = ::tolower(c);
		for(auto& c : right) c = ::tolower(c);
	}

	return left.compare(right);
}

void toUpper(string & s)
{
	for(auto& c : s) c = ::toupper(c);
}

void toLower(string & s)
{
	for(auto& c : s) c = ::tolower(c);
}

} // psin