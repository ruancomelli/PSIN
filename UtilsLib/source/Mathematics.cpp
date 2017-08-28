#include <Mathematics.hpp>

namespace psin {
	
unsigned long factorial( const unsigned n ){ 
  unsigned long nFactorial = 1;
	
	for( unsigned k = 1 ; k <= n ; ++k )
		nFactorial *= k;
	
	return nFactorial;
}

} // psin