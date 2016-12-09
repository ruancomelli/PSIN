#include <StringUtils.h>

// Compare char* case insensitive
int stringCompare( const string & left, const string & right )
{
	string l = left;
	string r = right;

	transform( left.begin(), left.end(), l.begin(), tolower );
	transform( right.begin(), right.end(), r.begin(), tolower );

	return strcmp( l.c_str() , r.c_str() );
}