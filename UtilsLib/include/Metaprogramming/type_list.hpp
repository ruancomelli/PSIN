#ifndef TYPE_LIST_HPP
#define TYPE_LIST_HPP

// UtilsLib / Traits
#include <Metaprogramming/type_list.tpp>

// Standard
#include <cstddef>
#include <type_traits>

template<typename...Ts>
struct type_list
{
	using identity = type_list<Ts...>;

	template<typename ... Us>
	using append = type_list<Ts..., Us...>;

	template<typename...Us>
	using append_if_new_types = typename traits::append_if_new_types<identity, Us...>::type;

	template<typename ... Us>
	using prepend = type_list<Us..., Ts...>;

	template<typename U, typename ... Us>
	constexpr static bool contains = traits::contains<identity, U, Us...>::value;

	constexpr static bool is_empty = traits::is_empty<Ts...>::value;

	constexpr static bool has_repeated_types = traits::has_repeated_types< type_list<Ts...> >::value;

	constexpr static std::size_t size = traits::size< identity >::value;

	template<template<typename...> class ClassToSpecialize>
	using specialize = ClassToSpecialize<Ts...>;

	template<typename TypeList>
	using concatenate = typename traits::concatenate<identity, TypeList>::type;

	template<std::size_t position>
	using get = typename traits::get<identity, position>::type;

	// template<typename TypeList>
	// using intersection = typename traits::intersection<TypeList>;
};

#endif

// WARNING: The use of this is, e.g., 'static_assert( std::is_same< type_list<int>::append<double> , type_list<int, double> >::value );'
// That is, 'type_list<Ts...>::append<T>' is the same as 'type_list<Ts..., T>'.
// The problem is that, in 'std::' syntax, there is a 'type', as in
// 		std::conditional<true, int, double>::type;
// Should we change our code? If so, this would change a lot the 'type_list', and the implementation would be more polluted... Or maybe not!