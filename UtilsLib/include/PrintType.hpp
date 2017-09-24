#ifndef PRINT_TYPE_HPP
#define PRINT_TYPE_HPP

#include <string.hpp>

namespace psin {

template<typename>
struct NamedType;

template<template<typename...> class>
struct NamedGroup;

namespace detail {

template<typename...Ts>
struct print_type_sequence;

template<typename T, typename...Ts>
struct print_type_sequence<T>
{
	const static string value = NamedType<T>::name + "," + print_type_sequence<Ts...>::value;
}

template<typename T>
struct print_type_sequence<T>
{
	const static string value = NamedType<T>::name;
}

} // detail

template<typename T>
struct print_type
{
	const static string value = NamedType<T>::name;
};

template<template<typename...> class T, typename...Ts>
struct print_type< T<Ts...> >
{
	const static string value = NamedGroup<T>::name + "<" + detail::print_type_sequence<Ts...>::value + ">";
};

template<template<typename...> class T>
struct print_type< T<> >
{
	const static string value = NamedGroup<T>::name + "<>";
};

} // psin

#endif // PRINT_TYPE_HPP
