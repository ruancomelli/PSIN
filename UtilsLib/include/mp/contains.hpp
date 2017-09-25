#ifndef CONTAINS_HPP
#define CONTAINS_HPP

#include <mp/bool_constant.hpp>

namespace psin {
namespace mp {

template<typename TypeList, typename...ContainedTypes>
struct contains;

template<typename TypeList>
struct contains<TypeList> : std::true_type {};

template<typename TypeList, typename U, typename...Us>
struct contains<TypeList, U, Us...>
	: mp::bool_constant< contains<TypeList, U>::value and contains<TypeList, Us...>::value >
{};

template<template<typename...> class TypeContainer, typename U>
struct contains< TypeContainer<>, U > : std::false_type {};

template<template<typename...> class TypeContainer, typename T, typename...Ts, typename U>
struct contains< TypeContainer<T, Ts...>, U >
	: mp::bool_constant< std::is_same<T, U>::value or contains< TypeContainer<Ts...>, U>::value >
{};

} // mp
} // psin

#endif // CONTAINS_HPP
