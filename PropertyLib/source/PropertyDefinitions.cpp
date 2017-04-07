#include <PropertyDefinitions.hpp>

// Standard
#include <iostream>

void PropertyDefinitions::setPositive( const double & value, double & destination)
{
	if(value > 0) destination = value;
	else std::cerr << "Error: Input value must be positive.";
}

PropertyDefinitions::Mass::Mass()
	: Property<double>("Mass", setPositive)
{}

PropertyDefinitions::Volume::Volume()
	: Property<double>("Volume", setPositive)
{}

PropertyDefinitions::MomentOfInertia::MomentOfInertia()
	: Property<double>("MomentOfInertia", setPositive)
{}

PropertyDefinitions::ElasticModulus::ElasticModulus()
	: Property<double>("ElasticModulus", setPositive)
{}

PropertyDefinitions::DissipativeConstant::DissipativeConstant()
	: Property<double>("DissipativeConstant")
{}

PropertyDefinitions::PoissonRatio::PoissonRatio()
	: Property<double>("PoissonRatio")
{}

PropertyDefinitions::NormalDissipativeConstant::NormalDissipativeConstant()
	: Property<double>("NormalDissipativeConstant", setPositive)
{}

PropertyDefinitions::TangentialDamping::TangentialDamping()
		: Property<double>("TangentialDamping", setPositive)
{}

PropertyDefinitions::FrictionParameter::FrictionParameter()
		: Property<double>("FrictionParameter", setPositive)
{}

PropertyDefinitions::TangentialKappa::TangentialKappa()
		: Property<double>("TangentialKappa", setPositive)
{}

PropertyDefinitions::ElectricCharge::ElectricCharge()
		: Property<double>("ElectricCharge", setPositive)
{}