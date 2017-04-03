#include <StringUtils.hpp>

// Standard
#include <algorithm>

// Compare strings case sensitive or not
int stringCompare( std::string left, std::string right, bool caseSensitive )
{
	if(!caseSensitive)
	{
		for(auto& c : left) c = ::tolower(c);
		for(auto& c : right) c = ::tolower(c);
	}

	return left.compare(right);
}