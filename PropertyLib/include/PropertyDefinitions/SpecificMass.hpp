#ifndef SPECIFIC_MASS_HPP
#define SPECIFIC_MASS_HPP

// JSONLib
#include <json.hpp>

// PropertyLib
#include <PositiveProperty.hpp>

namespace psin {
	
struct SpecificMass : public PositiveProperty<double>
{
	SpecificMass() = default;
	SpecificMass(const SpecificMass &) = default;
	SpecificMass(SpecificMass &&) = default;
	SpecificMass& operator=(const SpecificMass &) = default;
	SpecificMass& operator=(SpecificMass &&) = default;
	virtual ~SpecificMass() = default;

	SpecificMass(const double & value);
};
void from_json(const json& j, SpecificMass &);
void to_json(json& j, const SpecificMass &);

} // psin

#endif // SPECIFIC_MASS_HPP
