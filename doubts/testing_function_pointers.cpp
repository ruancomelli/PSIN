
#include <cmath>
#include <iostream>

using namespace std;


template <typename T>
class FunctionPointer{
	public:
		void setPointer(T (*function)(int) ){
			ptr = function;
		}
		
		T (*ptr)(int);
};


int squareInt(int x){
	return x*x;
}


double rootOfInt(int x){
	return sqrt(x);
}


class TwoFunctions{
	public:
		FunctionPointer <int> intPointer;
		FunctionPointer <double> doublePointer;
};


int main(void){
	TwoFunctions twoFunctions;
	
	// This is a way of doing so (but it recquires ptr to be a public member)
	twoFunctions.intPointer.ptr = squareInt;
	twoFunctions.doublePointer.ptr = rootOfInt;
	
	// This also works
	twoFunctions.intPointer.ptr = &squareInt;
	twoFunctions.doublePointer.ptr = &rootOfInt;
	
	// This is another way, and is probably the best
	twoFunctions.intPointer.setPointer(squareInt);
	twoFunctions.doublePointer.setPointer(rootOfInt);
	
	cout << endl <<
	twoFunctions.intPointer.ptr(2) << endl <<
	twoFunctions.doublePointer.ptr(2) << endl;
}

/*
	Conclusions: 
	
	It is indeed possible to point to functions. The pointer must be declared as
	
		type (*pointer)(type1 arg1, type2 arg2, ..., type_n arg_n)
		
	where type1, ..., type_n must be well defined types and type can be a template.
	We can assign a function to the pointer by doing
	
		pointer = function
	or
	
		pointer = &function
		
	It is also possible to do this assignment through a function call, something like
	
		functionAssignToPointer( type (*function)(type1 arg1, type2 arg2, ..., type_n arg_n) ){
			pointer = function;
		}
		
	where type, type1, ... type_n must follow the same rules as stated before.
	
	
	What should be done in the future:
	Remove the "ptr" from this code, i.e., implement a code in which it is possible to do
		
		twoFunctions.intPointer = squareInt
		
	and to calculate
	
		twoFunctions.intPointer(2)
		
	
	Further conclusions:
	
	I realized that I just complicated what I wanted to do.
*/