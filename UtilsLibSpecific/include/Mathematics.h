// MATHEMATICS

#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#define _USE_MATH_DEFINES

#include <cmath>

// factorial:
//	Calculates n!, where n is a nonnegative integer
inline unsigned long factorial( unsigned n ){ 
  unsigned long nFactorial = 1;
	
	for( unsigned k = 1 ; k <= n ; ++k )
		nFactorial *= k;
	
	return nFactorial;
}


#endif