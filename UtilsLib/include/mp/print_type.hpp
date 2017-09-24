#ifndef PRINT_TYPE_HPP
#define PRINT_TYPE_HPP

#include <string.hpp>

namespace psin {

template<typename>
struct NamedType;

template<template<typename...> class>
struct NamedGroup;

namespace detail {

template<typename T, typename...Ts>
struct PrintTypeSequence
{
	const static string value = NamedType<T>::name + "," + PrintTypeSequence<Ts...>::value;
};

template<typename T>
struct PrintTypeSequence<T>
{
	const static string value = NamedType<T>::name;
}

} // detail

template<typename T>
struct PrintType
{
	const static string value = NamedType<T>::name;
};

template<template<typename...> class T, typename...Ts>
struct PrintType< T<Ts...> >
{
	const static string value = NamedGroup<T>::name + "<" + detail::print_type_sequence<Ts...>::value + ">";
};

template<template<typename...> class T>
struct PrintType< T<> >
{
	const static string value = NamedGroup<T>::name + "<>";
};

} // psin

#endif // PRINT_TYPE_HPP
