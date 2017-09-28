#ifndef IS_EMPTY_HPP
#define IS_EMPTY_HPP

#include <mp/bool_constant.hpp>

namespace psin {
namespace mp {

template<typename T>
struct is_empty;

template<template<typename...> class T, typename...Ts>
struct is_empty< T<Ts...> >
	: mp::bool_constant< sizeof...(Ts) == 0 >
{};

} // mp
} // psin

#endif // IS_EMPTY_HPP
