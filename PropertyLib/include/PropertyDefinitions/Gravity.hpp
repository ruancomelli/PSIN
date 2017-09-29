#ifndef GRAVITY_HPP
#define GRAVITY_HPP

// JSONLib
#include <json.hpp>

// PropertyLib
#include <Property.hpp>

// UtilsLib
#include <Vector3D.hpp>

namespace psin {
	
struct Gravity : public Property<Vector3D>
{
	Gravity();
	Gravity(const Vector3D & value);
};
void from_json(const json& j, Gravity &);
void to_json(json& j, const Gravity &);

} // psin

#endif // GRAVITY_HPP
