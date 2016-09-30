/*
Some doubts we have, and we solved it with this program:
1. Can we sum a 'enum Type' with a 'int'?
2. Can we use a 'enum Type' as it was a 'int'?
*/
#include <iostream>

using namespace std;

enum Number{ ONE=1, TWO, THREE };
void print(int);

int main(){

	// Solving 1.
	int i=0;
	Number a=ONE;
	cout << (i+a) << endl << endl;
	
	// Solving 2.
	print(TWO);
	
	return 0;
}

void print(int i)
{
	cout << "print: " << i << endl << endl;
}
