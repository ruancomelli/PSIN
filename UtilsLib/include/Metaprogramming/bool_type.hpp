#ifndef BOOL_TYPE_HPP
#define BOOL_TYPE_HPP

#include <type_traits>

template<bool X>
struct bool_type 
	: std::conditional<
		X,
		std::true_type,
		std::false_type
	>::type
{};

#endif
