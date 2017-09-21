#include <Named.hpp>

namespace psin {

const std::string Named::defaultName = "Nameless";

// Constructors
Named::Named(void)
	: name(defaultName)
{
}

Named::Named(const string & name)
{
	this->setName(name);
}

// Set and get name
void Named::setName(const string & name)
{
	if(!name.empty()) this->name = name;
	else this->name = defaultName;
}

std::string Named::getName(void) const
{
	return this->name;
}


bool operator<(const Named & left, const Named & right)
{
	Named::NamedCompare namedCompareObject;
	return namedCompareObject(left, right);
}

void from_json(const json & j, Named & named)
{
	named = Named(j.at("Name").get<string>());
}

void to_json(json & j, const Named & named)
{
	j = json{
		{"Name", named.getName()}
	};
}

} // psin