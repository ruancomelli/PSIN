#ifndef GRAVITY_FIELD_HPP
#define GRAVITY_FIELD_HPP

// UtilsLib
#include <Named.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// EntityLib
#include <FixedBoundary.hpp>

namespace psin {

class GravityField
	: public FixedBoundary<Gravity>
{
public:
	using BaseFixedBoundary = FixedBoundary<Gravity>;

	GravityField() = default;
	GravityField(const BaseFixedBoundary & fixed);
};

void from_json(const json& j, GravityField & g);
void to_json(json& j, const GravityField & g);

} // psin

#endif // GRAVITY_FIELD_HPP
