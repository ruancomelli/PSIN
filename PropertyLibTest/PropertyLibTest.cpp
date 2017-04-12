#define BOOST_TEST_MODULE PropertyLibTest

// Standard
#include <iostream>
#include <fstream>
#include <iterator>

// PropertyLib
#include <Property.hpp>
#include <Property.hpp>

// UtilsLib
#include <Test.hpp>

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
	string string1 = "Steve";
	string string2 = "Rohan";

	int destination;
	int destinationAnswer = string1.length();

	// Default constructor - Test compilation
	Property<string, int> myProperty1;

	// Passing setter and getter functions - Passing function pointers
	Property<string, int> myProperty2(setIntFromString, getStringFromInt);

	myProperty2.setter( string1, destination );
	checkEqual( destination, destinationAnswer );
	checkEqual( myProperty2.getter(6), "6" );


	// Passing setter and getter functions - Passing lambda expressions
	Property<string, int> myProperty3( 
		[](const string & value, int & destination){ destination = value.length(); }, 
		[](const int & value){ return to_string(value); });

	myProperty3.setter( string2, destination );
	checkEqual( destination, string2.length() );
	checkEqual( myProperty3.getter(6), "6" );

}

TestCase(PropertyWithSameTemplateConstructorsTest)
{
	int destination;

	Property<int> myProperty1;
	Property<int> myProperty2(setIntAsDouble, getIntAsTriple);
	Property<int, int> myProperty3;

	// Check setter and getter functions
	myProperty1.setter(5, destination);
	checkEqual(5, destination);
	checkEqual(7, myProperty1.getter(7));

	myProperty2.setter(8, destination);
	checkEqual(8, destination);
	checkEqual(15, myProperty2.getter(15));

	myProperty2.setter(30, destination);
	checkEqual(destination, 60);
	checkEqual(myProperty2.getter(33), 99);

	// The following code results in runtime error, for myProperty3.setter is NULL

	//myProperty3.setter(10, destination);
	//checkEqual(destination, 10);
	//checkEqual(myProperty3.getter(12), 12);
}

TestCase(PropertySetSetterAndGetterTest)
{
	string name = "Rohan";
	int destination;
	int destinationAnswer = name.length();

	Property<string, int> myProperty;

	myProperty.setSetterFunction(setIntFromString);
	myProperty.setGetterFunction(getStringFromInt);

	myProperty.setter(name, destination);

	checkEqual(destination, destinationAnswer);
	checkEqual(myProperty.getter(6), "6");
}

TestCase(EqualFunctionsTest)
{
	check(setIntFromString == setIntFromString);
	check(setIntFromString != setIntFromString2);
}


#include <PropertyContainer.hpp>
#include <ValuedPropertyContainer.hpp>
#include <PropertyDefinitions.hpp>

using namespace PropertyDefinitions;

TestCase(PropertyContainerTest)
{
	PropertyContainer<Mass, Volume> raw;
	raw.insertProperty<Mass>();

	SharedPointer< set<string> > nameSet = raw.getPropertyNames();
	set<string>::iterator it = nameSet->begin();

	checkEqual( *it, Mass::name );

	PropertyContainer<Mass, Volume> raw2(raw);
	raw2.insertProperty<Volume>();

	nameSet = raw.getPropertyNames();
	it = nameSet->find( Volume::name );

	checkEqual(*it, Volume::name);

	// Testing set and get input and output methods
	Property<double> newProperty;
	newProperty.setInputMethod(defaultInputMethod<double>);
	newProperty.setOutputMethod(defaultOutputMethod<double>);

	raw2.insertProperty<Property<double>>();

	// Test if raw2.getInputMethod( newProperty.getName() ) == defaultInputMethod<double>
	// and raw2.getOutputMethod(newProperty.getName()) == defaultOutputMethod<double>
}

struct Color : Property<string>
{
	Color()
	{}

	static const std::string name;
};
const std::string Color::name = "Color";

struct Integer : Property<int>
{
	Integer()
	{}

	static const std::string name;
};
const std::string Integer::name = "Integer";

TestCase(ValuedPropertyContainerTest)
{
	double massValue = 80.5;
	double volumeValue = 10.0;
	string colorValue = "blue";
	int intValue = 5;

	std::vector< Any > valueList;
	set<string> nameList;

	ValuedPropertyContainer<Mass, Color, Integer, Volume> valuedPropertyContainer;

	valuedPropertyContainer.setProperty(Mass(), massValue);
	valuedPropertyContainer.setProperty(Color(), colorValue);
	valuedPropertyContainer.setProperty(Integer(), intValue);
	valuedPropertyContainer.setProperty(Volume(), volumeValue);

	checkEqual(valuedPropertyContainer.getValue(Mass()), massValue);
	checkEqual(valuedPropertyContainer.getValue(Color()), colorValue);
	checkEqual(valuedPropertyContainer.getValue(Integer()), intValue);
	checkEqual(valuedPropertyContainer.getValue(Volume()), volumeValue);

	check(valuedPropertyContainer.checkSetted(Mass()));
	check(valuedPropertyContainer.checkSetted(Color::name));
	check(!valuedPropertyContainer.checkSetted("length"));	// Checks that "length" was not set

	PropertyContainer<Mass> raw;
	raw.insertProperty<Mass>();

	ValuedPropertyContainer<Mass> propertyContainer2(raw);
	SharedPointer<set<string>> nameSet = propertyContainer2.getPropertyNames();
	set<string>::iterator it = nameSet->find(Mass::name);
	
	checkEqual( *it, Mass::name );

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
	Property<double> mass;
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
