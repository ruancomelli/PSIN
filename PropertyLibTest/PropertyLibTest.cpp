#define BOOST_TEST_MODULE PropertyLibTest

// Standard
#include <iostream>
#include <iterator>

// PropertyLib
#include <Property.h>

// UtilsLib
#include <Test.h>

using std::string;

void setIntFromString(const string & value, int & destination)
{
	destination = value.length();
}

void setIntFromString2(const string & value, int & destination)
{
	destination = 2*value.length();
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

	// Check names
	checkEqual(raw1.getName(), defaultName);
	checkEqual(raw2.getName(), name);
	checkEqual(raw3.getName(), otherName);
	checkEqual(raw4.getName(), defaultName);

	// Check setter and getter functions
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

TestCase(EqualFunctionsTest)
{
	check(setIntFromString == setIntFromString);
	check(setIntFromString != setIntFromString2);
}

TestCase(EqualAndSimilarTest)
{
	RawProperty<string, int> raw1("Rohan");
	RawProperty<string, int> raw2("Rohan");
	RawProperty<string, int> raw3("Rohan", setIntFromString, getStringFromInt);
	RawProperty<string, int> raw4("Rohan", setIntFromString, getStringFromInt);
	RawProperty<string, int> raw5("Steve", setIntFromString, getStringFromInt);


	check(raw1.isSimilarTo(raw2));
	check(raw1.isSimilarTo(raw3));
	check(!raw1.isSimilarTo(raw5));

	check(raw1.isEqualTo(raw2));
	check(raw3.isEqualTo(raw4));
	check(!raw2.isEqualTo(raw3));
	check(!raw1.isEqualTo(raw5));

	RawProperty<int> raw6("Rohan");
	RawProperty<int> raw7("Rohan");
	RawProperty<int, int> raw8("Rohan");
	RawProperty<int, int> raw9("Rohan", defaultSetter, defaultGetter);

	check(raw6.isEqualTo(raw7));
	check(raw6.isSimilarTo(raw8));
	check(!raw6.isEqualTo(raw8));
	check(raw6.isEqualTo(raw9));

}

TestCase(PropertyConstructorsTest)
{
	string defaultName = "Nameless";
	string name = "Bilbo";
	string value = "Gondor";
	string rawName = "Raw";

	RawProperty<string, int> raw(rawName, setIntFromString, getStringFromInt);

	Property<string, int> property1;
	Property<string, int> property2(name);
	Property<string, int> property3(name, setIntFromString, getStringFromInt);
	Property<string, int> property4(raw);
	Property<string, int> property5(raw, value);

	// Check names
	checkEqual(property1.getName(), defaultName);
	checkEqual(property2.getName(), name);
	checkEqual(property3.getName(), name);
	checkEqual(property4.getName(), rawName);
	checkEqual(property5.getName(), rawName);

	// Set and Get
	property3.set(value);
	checkEqual(property3.get(), to_string(value.length()));

	property4.set(value);
	checkEqual(property4.get(), to_string(value.length()));

	checkEqual(property5.get(), to_string(value.length()));
}

TestCase(PropertyConstructorsWithSameTemplateParametersTest)
{
	string defaultName = "Nameless";
	string name = "Bilbo";
	int value = 8;
	int returnValue = 8 * 6;
	string rawName = "Raw";

	RawProperty<int> raw(rawName, setIntAsDouble, getIntAsTriple);

	Property<int> property1;
	Property<int> property2(name);
	Property<int> property3(name, setIntAsDouble, getIntAsTriple);
	Property<int> property4(raw);
	Property<int> property5(raw, value);

	// Check names
	checkEqual(property1.getName(), defaultName);
	checkEqual(property2.getName(), name);
	checkEqual(property3.getName(), name);
	checkEqual(property4.getName(), rawName);
	checkEqual(property5.getName(), rawName);

	// Set and Get
	property1.set(value);
	checkEqual(property1.get(), value);

	property2.set(value);
	checkEqual(property2.get(), value);

	property3.set(value);
	checkEqual(property3.get(), returnValue);

	property4.set(value);
	checkEqual(property4.get(), returnValue);

	checkEqual(property5.get(), returnValue);
}

TestCase(PropertySetRawProperty)
{
	string rawName = "Raw";

	string stringValue = "Sauron";
	string stringReturn = to_string( stringValue.length() );
	
	int intValue = 10;
	int intReturn = 6 * 10;

	RawProperty<string, int> raw1(rawName, setIntFromString, getStringFromInt);
	RawProperty<int> raw2(rawName, setIntAsDouble, getIntAsTriple);

	Property<string, int> property1;
	Property<int> property2;

	property1.setRawProperty(raw1);
	property2.setRawProperty(raw2);

	property1.set(stringValue);
	checkEqual(property1.get(), stringReturn);

	property2.set(intValue);
	checkEqual(property2.get(), intReturn);
}

#include <PropertyContainer.h>
#include <PropertyList.h>

using namespace PropertyList;

TestCase(PropertyContainerTest)
{
	set<string> x;
	set<string>::iterator it = x.find("Oi");

	double massValue = 80.5;
	double volumeValue = 10.0;
	string colorValue = "blue";
	int intValue = 5;

	many valueList;
	set<string> nameList;

	PropertyContainer propertyContainer;

	RawProperty<string> color("Color");
	RawProperty<int> integer("Integer");

	propertyContainer.setProperty(mass, massValue);
	propertyContainer.setProperty(volume, volumeValue);
	propertyContainer.setProperty(color, colorValue);

	checkEqual(propertyContainer.getValue(mass), massValue);
	checkEqual(propertyContainer.getValue(volume), volumeValue);
	checkEqual(propertyContainer.getValue(color), colorValue);
}