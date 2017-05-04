#define BOOST_TEST_MODULE PropertyLibTest

// Standard
#include <iostream>
#include <fstream>
#include <iterator>

// PropertyLib
#include <Property.hpp>
#include <PropertyDefinitions.hpp>

// UtilsLib
#include <Test.hpp>

using namespace PropertyDefinitions;
using namespace std;

TestCase(PropertyConstructorsTest)
{
	double tolerance = 1e-12;
	double value = 3.14;

	// Test default constructor
	Property<double> property1;
	check(!property1.assigned());

	property1.set(value);
	check(property1.assigned());
	checkClose(property1.get(), value, tolerance);

	// Test Property<double>(const double & value)
	Property<double> property2(value);
	check(property2.assigned());
	checkClose(property2.get(), value, tolerance);
}

TestCase(PropertyInputAndOutputTest)
{
	double tolerance = 1e-12;
	double value = 3.14;

	string fileName = "Property_Input_Output_Test.txt";
	fstream file(fileName, fstream::in | fstream::out | fstream::trunc);

	Property<double> property1(value);
	property1.output(file);

	file.clear();
	file.seekg(0, ios::beg);

	Property<double> property2;
	property2.input(file);

	check(property2.assigned());
	checkClose(property2.get(), value, tolerance);
}

TestCase(PropertyDefinitionsTest)
{
	string massName = "Mass";
	double positiveValue = 3.14;
	double negativeValue = -8.5;
	double tolerance = 1e-12;

	checkEqual(Mass::name, massName);

	Mass mass;

	mass.set(positiveValue);
	check(mass.assigned());
	checkClose(mass.get(), positiveValue, tolerance);

	mass.set(negativeValue);
	check(!mass.assigned());
	checkClose(mass.get(), positiveValue, tolerance);
}


