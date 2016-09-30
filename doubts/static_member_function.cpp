// Testing static member functions

#include <iostream>

using namespace std;

class Myclass
{
	public:
		static void print();
};


// Do not put 'static' in function implementation.
void Myclass::print()
{
	cout << endl << "Myclass::print called" << endl << endl;
}

/* ERRO:

static void Myclass::print()
{
	cout << endl << "Myclass::print called" << endl << endl;
}

*/


int main()
{
	Myclass::print();

	return 0;
}
