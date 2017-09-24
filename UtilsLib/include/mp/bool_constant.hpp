#ifndef BOOL_CONSTANT_HPP
#define BOOL_CONSTANT_HPP

#include <type_traits>

namespace psin {
namespace mp {

#ifdef __cpp_lib_bool_constant

using std::bool_constant;

#else

template<bool X>
struct bool_constant 
	: std::integral_constant<bool, X>
{};

#endif

} // mp
} // psin


#endif // BOOL_CONSTANT_HPP
