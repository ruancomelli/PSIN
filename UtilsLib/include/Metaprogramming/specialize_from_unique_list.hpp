#ifndef SPECIALIZE_FROM_UNIQUE_LIST_HPP
#define SPECIALIZE_FROM_UNIQUE_LIST_HPP

// UtilsLib
#include <Metaprogramming/make_unique_type_list.hpp>
#include <Metaprogramming/type_list.hpp>


template<template<typename...> class T, typename U>
struct specialize_from_type_list;

template<template<typename...> class T, typename...Ts>
struct specialize_from_type_list<T, type_list<Ts...> >
{
	using type = T<Ts...>;
};

template< template<typename...> class T , typename ... RepeatedArgs >
struct specialize_from_unique_list
{
	using type = typename specialize_from_type_list<
		T,
		make_unique_type_list<RepeatedArgs...>
	>::type;
};


#endif

