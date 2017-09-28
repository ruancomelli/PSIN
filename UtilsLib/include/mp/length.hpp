#ifndef LENGTH_HPP
#define LENGTH_HPP

// Standard
#include <type_traits>

namespace psin {
namespace mp {
	template<typename T>
	struct length;

	template<template<typename...> class TypeList, typename...Ts>
	struct length< TypeList<Ts...> >
		: std::integral_constant<std::size_t, sizeof...(Ts)>
	{};
} // mp
} // psin

#endif // LENGTH_HPP
