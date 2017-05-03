#define BOOST_TEST_MODULE PropertyLibTest

// Standard
#include <iostream>
#include <fstream>
#include <iterator>

// PropertyLib
#include <Property.hpp>
#include <PropertyContainer.hpp>
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

TestCase(PropertyContainerInstantiationTest)
{
	PropertyContainer<int, double, char> propertyContainerSuccess;

	//Uncomment the following line to get compile errors:
	//PropertyContainer<int, double, double> propertyContainerFail;
}

TestCase(PropertyContainerPropertyTest)
{
	int intValue = 3;
	double doubleValue = 5.6;

	PropertyContainer<int, double> propertyContainer;
	propertyContainer.property<int>() = intValue;
	propertyContainer.property<double>() = doubleValue;

	checkEqual(propertyContainer.property<int>(), intValue);
	checkEqual(propertyContainer.property<double>(), doubleValue);

	auto x = propertyContainer.property<double>();
	x *= 2;

	// Check that propertyContainer.property<double>() didn't change
	checkEqual(propertyContainer.property<double>(), doubleValue);
}

struct ATest
{
	int f()
	{
		return 5;
	}
};

TestCase(PropertyContainerCallPropertyMemberFunctionTest)
{
	int returnValue = 5;
	PropertyContainer<ATest> propertyContainer;

	checkEqual(propertyContainer.property<ATest>().f(), returnValue);
}

struct TestedProperty : public Property<double>
{};

TestCase(PropertyContainerInputAndOutputTest)
{
	double tolerance = 1e-12;
	double defaultValue = 0.0;
	double value = 3.14;

	PropertyContainer<TestedProperty> inputter;
	PropertyContainer<TestedProperty> outputter;

	inputter.property<TestedProperty>().set(defaultValue);
	outputter.property<TestedProperty>().set(value);

	string fileName = "PropertyContainer_Input_Output_Test.txt";
	fstream file(fileName, fstream::in | fstream::out | fstream::trunc);

	outputter.output<TestedProperty>(file);

	file.clear();
	file.seekg(0, ios::beg);

	inputter.input<TestedProperty>(file);

	checkClose(inputter.property<TestedProperty>().get(), value, tolerance);
}

TestCase(MassInPropertyContainerTest)
{
	double massValue = 5;
	PropertyContainer<Mass> propertyContainer;

	check( !( propertyContainer.assigned<Mass>() ) );

	propertyContainer.property<Mass>().set(massValue);

	check(( propertyContainer.assigned<Mass>() ));

	checkEqual(propertyContainer.property<Mass>().get(), massValue);
}
