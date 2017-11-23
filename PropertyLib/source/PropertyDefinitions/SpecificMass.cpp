#ifndef SPECIFIC_MASS_CPP
#define SPECIFIC_MASS_CPP

#include <PropertyDefinitions/SpecificMass.hpp>

// JSONLib
#include <json.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <string.hpp>

// PropertyLib
#include <Property.hpp>

namespace psin {

SpecificMass::SpecificMass(const double & value)
	: PositiveProperty<double>(value)
{}

template<> const string NamedType<SpecificMass>::name = "SpecificMass";

void from_json(const json& j, SpecificMass & x)
{
	x = SpecificMass(j.get<double>());
}
void to_json(json& j, const SpecificMass & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

} // psin

#endif // SPECIFIC_MASS_CPP
