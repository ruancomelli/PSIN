#ifndef GET_HPP
#define GET_HPP

// Standard
#include <cstddef>

namespace traits {
	template<typename TypeList, std::size_t position>
	struct get;

	template<template<typename...> class TypeList, typename T, typename...Ts, std::size_t position>
	struct get<
		TypeList<T, Ts...>,
		position
	>
	{
		using type = typename get< TypeList<Ts...> , position - 1>::type;
	};

	template<template<typename...> class TypeList, typename T, typename...Ts>
	struct get<
		TypeList<T, Ts...>,
		0
	>
	{
		using type = T;
	};

	template<template<typename...> class TypeList, std::size_t position>
	struct get<
		TypeList<>,
		position
	>
	{
		static_assert( position >= 0,
			"'position' in 'TypeList::get<position>' must be less than 'TypeList::size' ");

		using type = void;
	};
} // traits

#endif // GET_HPP
