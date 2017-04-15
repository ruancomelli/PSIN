#include <iostream>

using namespace std;

struct X
{};

struct Y : public X
{
};

bool operator<(X x1, X x2)
{
	return true;
}

bool operator<(Y y1, Y y2)
{
	return false;
}

int main()
{
	X x1;
	X x2;
	Y y1;
	Y y2;

	cout << "The following values must be true:" << endl;
	cout << std::boolalpha << x1 < x2 << endl;
	cout << std::boolalpha << x1 < y1 << endl;
	cout << std::boolalpha << !(y1 < y2) << endl;
}