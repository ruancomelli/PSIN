// boost
#include <boost/spirit/hold_any.hpp>

// Standard
#include <iostream>

using namespace std;

typedef map<string, boost::spirit::hold_any> dictionary;

int main()
{
	dictionary dict;

	dict["int"] = 3;
	dict["string"] = "oi";

	cout << "dict[\"int\"] = " << dict["int"] << endl;
	cout << "dict[\"string\"] = " << dict["string"] << endl;
}