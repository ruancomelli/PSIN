#ifndef GRAVITY_FIELD_CPP
#define GRAVITY_FIELD_CPP

#include <GravityField.hpp>

// UtilsLib
#include <NamedType.hpp>

namespace psin {

template<>
const string NamedType<GravityField>::name = "GravityField";

void from_json(const json& j, GravityField & g)
{
	g = GravityField(j.get<GravityField::BaseFixedBoundary>());
}

void to_json(json& j, const GravityField & g)
{
	GravityField::BaseFixedBoundary fixed = g;

	j = fixed;
}

GravityField::GravityField(const BaseFixedBoundary & fixed)
	: BaseFixedBoundary(fixed)
{}

} // psin

#endif // GRAVITY_FIELD_CPP
