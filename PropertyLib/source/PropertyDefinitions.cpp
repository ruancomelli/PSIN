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
const std::string PropertyDefinitions::Mass::name = "Mass";

PropertyDefinitions::Volume::Volume()
	: Property<double>("Volume", setPositive)
{}
const std::string PropertyDefinitions::Volume::name = "Volume";

PropertyDefinitions::MomentOfInertia::MomentOfInertia()
	: Property<double>("MomentOfInertia", setPositive)
{}
const std::string PropertyDefinitions::MomentOfInertia::name = "MomentOfInertia";

PropertyDefinitions::ElasticModulus::ElasticModulus()
	: Property<double>("ElasticModulus", setPositive)
{}
const std::string PropertyDefinitions::ElasticModulus::name = "ElasticModulus";

PropertyDefinitions::DissipativeConstant::DissipativeConstant()
	: Property<double>("DissipativeConstant")
{}
const std::string PropertyDefinitions::DissipativeConstant::name = "DissipativeConstant";

PropertyDefinitions::PoissonRatio::PoissonRatio()
	: Property<double>("PoissonRatio")
{}
const std::string PropertyDefinitions::PoissonRatio::name = "PoissonRatio";

PropertyDefinitions::NormalDissipativeConstant::NormalDissipativeConstant()
	: Property<double>("NormalDissipativeConstant", setPositive)
{}
const std::string PropertyDefinitions::NormalDissipativeConstant::name = "NormalDissipativeConstant";

PropertyDefinitions::TangentialDamping::TangentialDamping()
		: Property<double>("TangentialDamping", setPositive)
{}
const std::string PropertyDefinitions::TangentialDamping::name = "TangentialDamping";

PropertyDefinitions::FrictionParameter::FrictionParameter()
		: Property<double>("FrictionParameter", setPositive)
{}
const std::string PropertyDefinitions::FrictionParameter::name = "FrictionParameter";

PropertyDefinitions::TangentialKappa::TangentialKappa()
		: Property<double>("TangentialKappa", setPositive)
{}
const std::string PropertyDefinitions::TangentialKappa::name = "TangentialKappa";

PropertyDefinitions::ElectricCharge::ElectricCharge()
		: Property<double>("ElectricCharge", setPositive)
{}
const std::string PropertyDefinitions::ElectricCharge::name = "ElectricCharge";