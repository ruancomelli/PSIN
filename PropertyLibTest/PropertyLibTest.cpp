#define BOOST_TEST_MODULE PropertyLibTest

// Standard
#include <iostream>

// PropertyLib
#include <Property.h>

// UtilsLib
#include <Test.h>

using std::string;

void setIntFromString(const string & value, int & destination)
{
	destination = value.length();
}

string getStringFromInt(const int & value)
{
	return to_string(value);
}

TestCase( RawPropertyConstructorsTest )
{
	string defaultName = "Nameless";
	string name = "Steve";
	string otherName = "Rohan";

	int destination;
	int destinationAnswer = otherName.length();

	RawProperty<string, int> raw1;
	//RawProperty<string, int> raw2(name);
	//RawProperty<string, int> raw3(otherName, setIntFromString, getStringFromInt);

	//checkEqual( raw1.getName(), defaultName );
	//checkEqual( raw2.getName(), name );
	//checkEqual( raw3.getName(), otherName );

	//raw3.setter( otherName, destination );

	//checkEqual( destination, destinationAnswer );
	//checkEqual( raw3.getter(6), "6" );
}