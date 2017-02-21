#ifndef PROPERTY_LIST_H
#define PROPERTY_LIST_H

// PropertyLib
#include <Property.h>

// Standard
#include <iostream>
#include <string>

using namespace std;

namespace PropertyList{

	// Assigns value to destination if value is positive
	void setPositive( const double & value, double & destination);

	// Mass
	static RawProperty<double> mass("Mass", setPositive);

	// Volume
	static RawProperty<double> volume("Volume", setPositive);

	// Moment of Inertia
	static RawProperty<double> moment_of_inertia("MomentOfInertia", setPositive);

};

#endif