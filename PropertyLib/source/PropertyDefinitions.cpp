#include <PropertyDefinitions.hpp>

// Standard
#include <iostream>

void PropertyDefinitions::setPositive( const double & value, double & destination)
{
	if(value > 0) destination = value;
	else std::cout << "Error: Input value must be positive.";
}