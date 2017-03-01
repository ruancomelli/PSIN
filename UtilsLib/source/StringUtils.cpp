#include <StringUtils.h>

// Compare strings case sensitive or not
int stringCompare( string left, string right, bool caseSensitive )
{
	if(!caseSensitive)
	{
		for(unsigned i = 0 ; i<left.length() ; ++i)
		{
			left[i] = tolower( left[i] );
		}
		for(unsigned i = 0 ; i<right.length() ; ++i)
		{
			right[i] = tolower( right[i] );
		}
	}

	return strcmp( left.c_str() , right.c_str() );
}