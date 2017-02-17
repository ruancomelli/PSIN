#include <PropertyList.h>

void setPositive( const double & value, double & destination)
{
	if(value > 0) destination = value;
	else std::cout << "Error: Input value must be positive.";
}