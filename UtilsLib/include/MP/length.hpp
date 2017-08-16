#ifndef LENGTH_HPP
#define LENGTH_HPP

// Standard
#include <type_traits>

namespace traits {
	template<typename T>
	struct length;

	template<template<typename...> class TypeList, typename...Ts>
	struct length< TypeList<Ts...> >
		: std::integral_constant<std::size_t, sizeof...(Ts)>
	{};
} // traits

#endif // LENGTH_HPP
