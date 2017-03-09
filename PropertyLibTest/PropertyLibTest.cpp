#define BOOST_TEST_MODULE PropertyLibTest

// Standard
#include <iostream>
#include <fstream>
#include <iterator>

// PropertyLib
#include <Property.h>
#include <Property.h>

// UtilsLib
#include <Test.h>

using std::string;

using namespace std;

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

TestCase( PropertyConstructorsTest )
{
	string defaultName = "Nameless";
	string name = "Steve";
	string otherName = "Rohan";

	int destination;
	int destinationAnswer = otherName.length();

	Property<string, int> raw1;
	Property<string, int> raw2(name);
	Property<string, int> raw3(otherName, setIntFromString, getStringFromInt);

	checkEqual( raw1.getName(), defaultName );
	checkEqual( raw2.getName(), name );
	checkEqual( raw3.getName(), otherName );

	raw3.setter( otherName, destination );

	checkEqual( destination, destinationAnswer );
	checkEqual( raw3.getter(6), "6" );
}

TestCase(PropertyWithSameTemplateConstructorsTest)
{
	string defaultName = "Nameless";
	string name = "Steve";
	string otherName = "Rohan";

	int destination;

	Property<int> raw1;
	Property<int> raw2(name);
	Property<int> raw3(otherName, setIntAsDouble, getIntAsTriple);
	Property<int, int> raw4;

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

TestCase(PropertySetSetterAndGetterTest)
{
	string name = "Rohan";
	int destination;
	int destinationAnswer = name.length();

	Property<string, int> raw;

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


#include <RawPropertyContainer.h>
#include <PropertyContainer.h>
#include <PropertyList.h>

using namespace PropertyList;

TestCase(RawPropertyContainerTest)
{
	RawPropertyContainer raw;
	raw.addProperty(mass);

	SharedPointer< set<string> > nameSet = raw.getPropertyNames();
	set<string>::iterator it = nameSet->begin();

	checkEqual( *it, mass.getName() );

	RawPropertyContainer raw2(raw);
	raw2.addProperty(volume);

	nameSet = raw.getPropertyNames();
	it = nameSet->find( volume.getName() );

	checkEqual(*it, volume.getName());

	// Testing set and get input and output methods
	Property<double> newProperty;
	newProperty.setInputMethod(defaultInputMethod<double>);
	newProperty.setOutputMethod(defaultOutputMethod<double>);

	raw2.addProperty(newProperty);

	// Test if raw2.getInputMethod( newProperty.getName() ) == defaultInputMethod<double>
	// and raw2.getOutputMethod(newProperty.getName()) == defaultOutputMethod<double>
}

TestCase(PropertyContainerTest)
{
	double massValue = 80.5;
	double volumeValue = 10.0;
	string colorValue = "blue";
	int intValue = 5;

	Property<string> color("Color");
	Property<int> integer("Integer");

	Many valueList;
	set<string> nameList;

	PropertyContainer propertyContainer;

	propertyContainer.setProperty(mass, massValue);
	propertyContainer.setProperty(color, colorValue);
	propertyContainer.setProperty(integer, intValue);
	propertyContainer.setProperty(volume, volumeValue);

	checkEqual(propertyContainer.getValue(mass), massValue);
	checkEqual(propertyContainer.getValue(color), colorValue);
	checkEqual(propertyContainer.getValue(integer), intValue);
	checkEqual(propertyContainer.getValue(volume), volumeValue);

	RawPropertyContainer raw;
	raw.addProperty(mass);

	PropertyContainer propertyContainer2(raw);
	SharedPointer<set<string>> nameSet = propertyContainer2.getPropertyNames();
	set<string>::iterator it = nameSet->find(mass.getName());
	
	checkEqual( *it, mass.getName() );

}

bool input2timesDouble(ifstream & in, Any & value)
{
	double x;
	in >> x;
	value = 2 * x;
	return true;
}

bool output3timesDouble(ofstream & out, Any & value)
{
	double x = anyCast<double>(value);
	out << 3 * x;
	return true;
}

TestCase(PropertyInputAndOutputTest)
{
	string fileName = "rawPropertyInputAndOutput.txt";
	Property<double> mass("Mass");
	double doubleValue = 5.6;

	Any value = doubleValue;
	Any secondValue;

	ofstream outFile(fileName);
	mass.outputMethod(outFile, value);
	outFile.close();

	ifstream inFile(fileName);
	mass.inputMethod(inFile, secondValue);
	inFile.close();
	
	checkClose(anyCast<double>(value), anyCast<double>(secondValue), 1e-10);

	mass.setInputMethod(input2timesDouble);
	mass.setOutputMethod(output3timesDouble);

	ofstream outFile2(fileName);
	mass.outputMethod(outFile2, value);
	outFile2.close();

	ifstream inFile2(fileName);
	mass.inputMethod(inFile2, secondValue);
	inFile2.close();

	checkClose( 6 * anyCast<double>(value), anyCast<double>(secondValue), 1e-10);
}
