#include <Named.hpp>

const std::string Named::defaultName = "Nameless";

// Constructors
Named::Named(void)
	: name("Nameless")
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
	else this->name = "Nameless";
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