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

void setIntAsDouble(const int & value, int & destination)
{
	destination = value * 2;
}

int getIntAsTriple(const int & value)
{
	return value * 3;
}

TestCase( RawPropertyConstructorsTest )
{
	string defaultName = "Nameless";
	string name = "Steve";
	string otherName = "Rohan";

	int destination;
	int destinationAnswer = otherName.length();

	RawProperty<string, int> raw1;
	RawProperty<string, int> raw2(name);
	RawProperty<string, int> raw3(otherName, setIntFromString, getStringFromInt);

	checkEqual( raw1.getName(), defaultName );
	checkEqual( raw2.getName(), name );
	checkEqual( raw3.getName(), otherName );

	raw3.setter( otherName, destination );

	checkEqual( destination, destinationAnswer );
	checkEqual( raw3.getter(6), "6" );
}

TestCase(RawPropertyWithSameTemplateConstructorsTest)
{
	string defaultName = "Nameless";
	string name = "Steve";
	string otherName = "Rohan";

	int destination;

	RawProperty<int> raw1;
	RawProperty<int> raw2(name);
	RawProperty<int> raw3(otherName, setIntAsDouble, getIntAsTriple);
	RawProperty<int, int> raw4;

	checkEqual(raw1.getName(), defaultName);
	checkEqual(raw2.getName(), name);
	checkEqual(raw3.getName(), otherName);
	checkEqual(raw4.getName(), defaultName);

	raw1.setter(5, destination);
	checkEqual(5, destination);
	checkEqual(7, raw1.getter(7));

	raw2.setter(8, destination);
	checkEqual(8, destination);
	checkEqual(15, raw2.getter(15));

	raw3.setter(30, destination);
	checkEqual(destination, 60);
	checkEqual(raw3.getter(33), 99);

	// The following code results in runtime error, for raw4.setter is NULL
	//raw4.setter(10, destination);
	//checkEqual(destination, 10);
	//checkEqual(raw4.getter(12), 12);
}

TestCase(RawPropertySetSetterAndGetterTest)
{
	string name = "Rohan";
	int destination;
	int destinationAnswer = name.length();

	RawProperty<string, int> raw;

	raw.setSetterFunction(setIntFromString);
	raw.setGetterFunction(getStringFromInt);

	raw.setter(name, destination);

	checkEqual(destination, destinationAnswer);
	checkEqual(raw.getter(6), "6");
}

TestCase(PropertyConstructorsTest)
{

}