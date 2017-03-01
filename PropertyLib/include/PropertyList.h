#ifndef PROPERTY_LIST_H
#define PROPERTY_LIST_H

// PropertyLib
#include <Property.h>

// Standard
#include <string>

namespace PropertyList{

	// Assigns value to destination if value is positive
	void setPositive( const double & value, double & destination);

	// Mass
	static Property<double> mass("Mass", setPositive);

	// Volume
	static Property<double> volume("Volume", setPositive);

	// Moment of inertia
	static Property<double> moment_of_inertia("MomentOfInertia", setPositive);

	// Elastic modulus
	static Property<double> elastic_modulus("ElasticModulus", setPositive);

	// Dissipative constant
	static Property<double> dissipative_constant("DissipativeConstant");

	// Poisson ratio
	static Property<double> poisson_ratio("PoissonRatio");

	// Normal Dissipative Constant
	static Property<double> normal_dissipative_constant("NormalDissipativeConstant", setPositive);

	// Tangential Damping
	static Property<double> tangential_damping("TangentialDamping", setPositive);

	// Friction Parameter
	static Property<double> friction_parameter("FrictionParameter", setPositive);

	// Tangential Kappa
	static Property<double> tangential_kappa("TangentialKappa", setPositive);

	// Electric Charge
	static Property<double> electric_charge("ElectricCharge");
};

#endif