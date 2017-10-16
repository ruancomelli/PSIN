#ifndef COLOR_HPP
#define COLOR_HPP

// JSONLib
#include <json.hpp>

// PropertyLib
#include <Property.hpp>

// UtilsLib
#include <string.hpp>
#include <Vector3D.hpp>

#include <utility>

namespace psin {

struct Color : Property< std::pair<Vector3D, string> >
{
	using BaseProperty = Property< std::pair<Vector3D, string> >;

	Color();
	Color(const string & colorName);
	Color(const Vector3D & colorRGB);

	json as_json() const;

	virtual ~Color() = default;

private:
	bool useRGB;
};

void from_json(const json & j, Color & c);
void to_json(json & j, const Color & c);

} // psin

#endif // COLOR_HPP
