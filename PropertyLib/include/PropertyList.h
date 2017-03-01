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

	// Moment of inertia
	static RawProperty<double> moment_of_inertia("MomentOfInertia", setPositive);

	// Elastic modulus
	static RawProperty<double> elastic_modulus("ElasticModulus", setPositive);

	// Dissipative constant
	static RawProperty<double> dissipative_constant("DissipativeConstant");

	// Poisson ratio
	static RawProperty<double> poisson_ratio("PoissonRatio");

	// Normal Dissipative Constant
	static RawProperty<double> normal_dissipative_constant("NormalDissipativeConstant", setPositive);

	// Tangential Damping
	static RawProperty<double> tangential_damping("TangentialDamping", setPositive);

	// Friction Parameter
	static RawProperty<double> friction_parameter("FrictionParameter", setPositive);

	// Tangential Kappa
	static RawProperty<double> tangential_kappa("TangentialKappa", setPositive);

	// Electric Charge
	static RawProperty<double> electric_charge("ElectricCharge");


};

#endif