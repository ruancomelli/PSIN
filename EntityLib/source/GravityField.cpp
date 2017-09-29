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
	Named named = j;
	GravityField::BaseFixedBoundary fixed = j;

	g = GravityField(named, fixed);
}

void to_json(json& j, const GravityField & g)
{
	Named named = g;
	GravityField::BaseFixedBoundary fixed = g;

	json jn = named;
	json jph = fixed;

	j = merge(jn, jph);
}

GravityField::GravityField(const Named & named, const BaseFixedBoundary & fixed)
	: BaseFixedBoundary(fixed)
{}

} // psin

#endif // GRAVITY_FIELD_CPP
