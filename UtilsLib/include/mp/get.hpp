#ifndef GET_HPP
#define GET_HPP

// UtilsLib
#include <mp/metafunction.hpp>

// Standard
#include <type_traits>

namespace psin {
namespace mp {

template<std::size_t position, typename TypeList>
struct get;

// Type version
template<template<typename...> class TypeList, typename T, typename...Ts, std::size_t position>
struct get<
	position,
	TypeList<T, Ts...>
> 
	: metafunction< 
		typename get< 
			position - 1, 
			TypeList<Ts...>
		>::type 
	>
{};

template<template<typename...> class TypeList, typename T, typename...Ts>
struct get<
	0,
	TypeList<T, Ts...>
> : metafunction<T>
{};

template<template<typename...> class TypeList, std::size_t position>
struct get<
	position,
	TypeList<>
>
{
	static_assert( position >= 0,
		"'position' in 'get<position, TypeList>' must be less than 'TypeList::size' ");

	using type = void;
};

} // mp
} // psin

#endif // GET_HPP
