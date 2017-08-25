#ifndef NAMED_TYPE_HPP
#define NAMED_TYPE_HPP

#include <string>

template<typename T>
struct NamedType
{
	const static std::string name;
}; //struct NamedType

#endif // NAMED_TYPE_HPP
