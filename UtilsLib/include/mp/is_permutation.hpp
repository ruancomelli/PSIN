#ifndef IS_PERMUTATION_HPP
#define IS_PERMUTATION_HPP

#include <mp/bool_constant.hpp>
#include <mp/contains.hpp>

namespace psin {
namespace mp {

template<typename T, typename U>
struct is_permutation;

template<template<typename...> class TypeContainer, typename...Ts, typename...Us>
struct is_permutation< TypeContainer<Ts...>, TypeContainer<Us...> >
	: bool_constant<
		contains<TypeContainer<Ts...>, Us...>::value
		and contains<TypeContainer<Us...>, Ts...>::value
	>
{};

} // mp
} // psin

#endif // IS_PERMUTATION_HPP
