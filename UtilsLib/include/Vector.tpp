#ifndef VECTOR_TPP
#define VECTOR_TPP

namespace psin {

template <class type> 
bool operator==( vector<type> & left , vector<type> & right ){
	if( left.size() == right.size() )
	{
		for( unsigned i = 0 ; i < left.size() ; ++i ){
			if( left[i] != right[i] ) return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

template <class type> 
bool operator!=( vector<type> & left , vector<type> & right ){
	return ! ( left==right );
}

} // psin

#endif
