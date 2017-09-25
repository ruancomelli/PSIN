#ifndef CONCATENATE_HPP
#define CONCATENATE_HPP

// UtilsLib
#include <mp/metafunction.hpp>

namespace psin {
namespace mp {

template<typename TypeList1, typename TypeList2>
struct concatenate;

template<template<typename...> class TypeList, typename...Is, typename...Js>
struct concatenate<
	TypeList<Is...>,
	TypeList<Js...>
> : metafunction< TypeList<Is..., Js...> >
{};

template<typename T, template<typename, T...> class TypeList, T...Is, T...Js>
struct concatenate<
	TypeList<T, Is...>,
	TypeList<T, Js...>
> : metafunction< TypeList<T, Is..., Js...> >
{};
	
} // mp
} // psin

#endif // CONCATENATE_HPP
