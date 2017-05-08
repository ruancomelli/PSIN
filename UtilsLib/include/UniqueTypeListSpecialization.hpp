#ifndef UTILS_UNIQUE_TYPE_LIST_SPECIALIZATION_HPP
#define UTILS_UNIQUE_TYPE_LIST_SPECIALIZATION_HPP


#include <EqualTypes.hpp>

template<typename...Ts>
struct type_list;

template<typename T, typename U>
struct prepend_type_to_type_list;

template<typename T, typename...Ts>
struct prepend_type_to_type_list<T, type_list<Ts...>>
{
	using value = type_list<T, Ts...>;
};

template<bool value, typename TrueResult, typename FalseResult>
struct if_then_else;

template<typename TrueResult, typename FalseResult>
struct if_then_else<true, TrueResult, FalseResult>
{
	using value = TrueResult;
};

template<typename TrueResult, typename FalseResult>
struct if_then_else<false, TrueResult, FalseResult>
{
	using value = FalseResult;
};

template<template<typename...> class T, typename U>
struct specialize_from_type_list;

template<template<typename...> class T, typename...Ts>
struct specialize_from_type_list<T, type_list<Ts...> >
{
	using value = T<Ts...>;
};

template<typename ... RepeatedArgs>
struct unique_type_list;

template<typename T, typename...Ts>
struct unique_type_list<T, Ts...>
{
	using value = typename if_then_else<
			type_is_in_list<T, Ts...>::value,
			typename unique_type_list<Ts...>::value,
			prepend_type_to_type_list<T, typename unique_type_list<Ts...>::value>
		>::value;
};

template<typename T>
struct unique_type_list<T>
{
	using value = type_list<T>;
};

template< template<typename...> class T , typename ... RepeatedArgs >
struct unique_type_list_specialization
{
	using value = specialize_from_type_list<
		T,
		typename unique_type_list<RepeatedArgs...>::value
	>;
};


#endif
