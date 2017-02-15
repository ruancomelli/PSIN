#ifndef PROPERTY_LIST_H
#define PROPERTY_LIST_H

#include <Property.h>
#include <string>

using namespace std;

// Assigns value to destination if value is positive
void setPositive( const double & value, double & destination);

// Mass
RawProperty<double> mass("Mass", setPositive);

// Volume
RawProperty<double> volume("Volume", setPositive);

#endif