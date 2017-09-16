#include <tuple>
#include <vector>

template<typename T, T...> constant_sequence;
template<typename...> type_list;

using std::tuple;
using std::vector;

void f(int& x)
{
	x *= 2;
}
void f(double x)
{
	x *= x;
}

int main()
{
	tuple< vector<int>, vector<double> > myTuple;
	for_type(T, type_list<int, double>)
	{
		T x; 
		f(x);
		get<T>(myTuple).insert(x);
	}

	// OR

	for(typename T, type_list<int, double>)
	{
		T x; 
		f(x);
		get<T>(myTuple).insert(x);
	}

	for(int x, constant_sequence<2, 3, 1>)
	{
		get<T>(myTuple).insert(x);
	}
}