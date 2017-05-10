#ifndef UTILS_UNIQUE_TYPE_LIST_SPECIALIZATION_HPP
#define UTILS_UNIQUE_TYPE_LIST_SPECIALIZATION_HPP

// UtilsLib
#include <EqualTypes.hpp>
#include <IfThenElse.hpp>
#include <UniqueTypeList.hpp>
#include <TypeList.hpp>


template<template<typename...> class T, typename U>
struct specialize_from_type_list;

template<template<typename...> class T, typename...Ts>
struct specialize_from_type_list<T, type_list<Ts...> >
{
	using value = T<Ts...>;
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
