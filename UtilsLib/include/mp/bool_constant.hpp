#ifndef BOOL_CONSTANT_HPP
#define BOOL_CONSTANT_HPP

#include <type_traits>

namespace psin {
namespace mp {

template<bool X>
struct bool_constant 
	: std::integral_constant<bool, X>
{};

} // mp
} // psin


#endif // BOOL_CONSTANT_HPP
