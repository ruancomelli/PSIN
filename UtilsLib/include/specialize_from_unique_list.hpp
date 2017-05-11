#ifndef UTILS_UNIQUE_TYPE_LIST_SPECIALIZATION_HPP
#define UTILS_UNIQUE_TYPE_LIST_SPECIALIZATION_HPP

// UtilsLib
#include <make_unique_type_list.hpp>
#include <type_list.hpp>


template<template<typename...> class T, typename U>
struct specialize_from_type_list;

template<template<typename...> class T, typename...Ts>
struct specialize_from_type_list<T, type_list<Ts...> >
{
	using value = T<Ts...>;
};

template< template<typename...> class T , typename ... RepeatedArgs >
struct specialize_from_unique_list
{
	using value = typename specialize_from_type_list<
		T,
		typename make_unique_type_list<RepeatedArgs...>::value
	>::value;
};


#endif

