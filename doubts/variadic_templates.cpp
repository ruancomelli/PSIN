#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

template<typename type>
struct A
{
	void print(void);
};

template<>
void A<int>::print(void)
{
	cout << "\t\tclass A :: print:" << endl
		<< "\t\tint" << endl;
}

template<>
void A<double>::print(void)
{
	cout << "\t\tclass A :: print:" << endl
		<< "\t\tdouble" << endl;
}

template<>
void A<string>::print(void)
{
	cout << "\t\tclass A :: print:" << endl
		<< "\t\tstring" << endl;
}

template<typename type>
struct B
{
	public:
		void print(void);
	private:
		A<type> a;
};

template<>
void B<int>::print(void)
{
	cout << "class B :: print:" << endl
		<< "int" << endl;
	this->a.print();
}

template<>
void B<double>::print(void)
{
	cout << "class B :: print:" << endl
		<< "double" << endl;
	this->a.print();
}

template<>
void B<string>::print(void)
{
	cout << "class B :: print:" << endl
		<< "string" << endl;
	this->a.print();
}

template<typename T>
void execute(B<T> t)
{
	t.print();
}

template<typename T, typename ... Args>
void execute(B<T> t, B<Args>... args)
{
	t.print();
	::execute(args...);
}



int main()
{
	B<int> bInt;
	B<double> bDouble;
	B<string> bString;

	::execute(bInt, bDouble, bString);
}

// SUCCESS
// What I have learned:
//
// It is possible to use variadic templates in C++11
// The elypsis (...) marks the pattern of template pack expansion
// As an example:

// template<typename T, typename ... Args>
// void execute(B<T> t, B<Args>... args);
//
// Can be called as execute(B<int>, B<double>, B<string>),
// because the pattern is B<Args>. That means that, for each
// type in Args list, a B<type> element is inserted.
//
// Now,
//
// template<typename T, typename ... Args>
// void execute(B<T> t, B<Args...> args);
//
// Can be called as execute(B<int>, B<double, string>)
// because the pattern is Args inside B<Args>. That means that, for each
// type in Args list, type element is inserted into B<Args>.

