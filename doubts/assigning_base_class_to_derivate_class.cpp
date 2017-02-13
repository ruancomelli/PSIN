// Tests assignment between base and derivate classes.
// suppose that derivate is an instance of a class Derivate,
// and that Derivate derivates from Base class, of which,
// base is an instance. Then what
// derivate = base
// does?

#include <iostream>
#include <string>

using namespace std;

class Base
{
	public:
		Base( string myName = "Nameless")
		{
			this->myName = myName;
			this->className = "Base";
		}

		void printNames(void)
		{
			cout << "Printing names:" << endl;
			cout << '\t' << "class name = " << className << endl;
			cout << '\t' << "my name = " << myName << endl;
		}

	private:
		string className;
		string myName;
};

class Derivate : public Base
{
	public:
		Derivate( string myName = "Nameless", int number = 5)
		{
			this->myName = myName;
			this->className = "Derivate";
			this->number = number;
		}

		void printMe(void)
		{
			printNames();
			cout << "Printing number:" << endl;
			cout << '\t' << "number = " << number << endl;
		}

	private:
		int number;
};

int main(void)
{
	Base base( "Steve" );
	Derivate derivate = base;

	derivate.printMe();
}

// Answer: It is possible, but not the way I wrote above.
// One solution is to implement a Derivate( Base base ) constructor.
// Another solution involves using pointers, but I didn't get it.