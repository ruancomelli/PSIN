#include <StringUtils.hpp>

// Standard
#include <algorithm>

namespace psin {

// Compare strings case sensitive or not
int stringCompare( const std::string & left, const std::string & right, const bool caseSensitive )
{
	if(!caseSensitive)
	{
		return asLower(left).compare( asLower(right) );
	}
	else
	{
		return left.compare(right);
	}
}

void toUpper(string & s)
{
	for(auto& c : s) c = ::toupper(c);
}

void toLower(string & s)
{
	for(auto& c : s) c = ::tolower(c);
}

string asUpper(string s)
{
	psin::toUpper(s);
	return s;
}

string asLower(string s)
{
	psin::toLower(s);
	return s;
}

} // psin