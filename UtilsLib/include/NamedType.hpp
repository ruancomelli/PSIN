#ifndef NAMED_TYPE_HPP
#define NAMED_TYPE_HPP

// UtilsLib
#include <string.hpp>

namespace psin {

template<typename T>
struct NamedType
{
	const static std::string name;
}; //struct NamedType

} // psin

#endif // NAMED_TYPE_HPP
