#include <StringUtils.h>

// Compare char* case insensitive
int stringCompare( string left, string right )
{
	transform( left.begin(), left.end(), left.begin(), tolower );
	transform( right.begin(), right.end(), right.begin(), tolower );

	return strcmp( left.c_str() , right.c_str() );
}