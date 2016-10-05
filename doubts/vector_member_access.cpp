#include <iostream>
#include <vector>

using namespace std;

typedef vector<double> DoubleVector;

int main()
{
	int i;
	const int n = 3;
	DoubleVector v;
	DoubleVector * vPtr = &v;

	// Initialize vector
	v.reserve(n);
	for(i=0 ; i<n ; i++)
	{
		v[i] = i;
	}
	cout << endl << endl;
	
	i = 1;
	cout << "v[" << i << "] = " << v[i] << " = " << (*vPtr)[i] << " = " << vPtr->operator[](i);
	// The statements
	// 	vPtr->[1]
	// 	vPtr[1]
	// don't work. But we can make a call to
	// 	operator[]
	// as done above.
	cout << endl << endl;

	return 0;
}

/*
I'd like to test if we could use pointers with the operator [].
We can, but the call must be done as:
	vPtr->operator[](input);
If we try:
	vPtr[1];
	vPtr->[1];
it will not work well.
*/
