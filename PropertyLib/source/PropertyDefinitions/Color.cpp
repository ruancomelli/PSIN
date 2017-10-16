#ifndef COLOR_CPP
#define COLOR_CPP

#include <PropertyDefinitions/Color.hpp>

// JSONLib
#include <json.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <string.hpp>
#include <Vector3D.hpp>

// PropertyLib
#include <Property.hpp>

namespace psin {

Color::Color()
	: BaseProperty(),
	useRGB(true)
{}

Color::Color(const string & colorName)
	: BaseProperty( std::make_pair(Vector3D(), colorName) ),
	useRGB(false)
{}

Color::Color(const Vector3D & colorRGB)
	: BaseProperty( std::make_pair(colorRGB, string()) ),
	useRGB(true)
{}

template<> const string NamedType<Color>::name = "Color";

json Color::as_json() const
{
	if(useRGB)
	{
		return json{
				this->get().first
			};
	}
	else
	{
		return json{
				this->get().second
			};
	}
}

void from_json(const json & j, Color & c)
{
	if(j.is_string())
	{
		c = Color(j.get<string>());
	}
	else if(j.is_array())
	{
		c = Color(j.get<Vector3D>());
	}
}

void to_json(json & j, const Color & c)
{
	j = c.as_json();
}

} // psin



#endif // COLOR_CPP
