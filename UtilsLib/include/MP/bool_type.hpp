#ifndef BOOL_TYPE_HPP
#define BOOL_TYPE_HPP

#include <type_traits>

template<bool X>
struct bool_type 
	: std::integral_constant<bool, X>
{};

#endif
