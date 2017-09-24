#ifndef RELATIVE_COMPLEMENT_HPP
#define RELATIVE_COMPLEMENT_HPP

#include <mp/concatenate.hpp>
#include <mp/contains.hpp>
#include <mp/metafunction.hpp>
#include <mp/type_list.hpp>

namespace psin {
namespace mp {

template<typename Pack1, typename Pack2>
struct relative_complement;

template<template<typename...> class Pack1, typename Pack2>
struct relative_complement<Pack1<>, Pack2>
	: mp::metafunction< Pack1<> >
{};

template<template<typename...> class Pack1, typename Pack2, typename T, typename...Ts>
struct relative_complement<Pack1<T, Ts...>, Pack2>
	: mp::metafunction<
		typename std::conditional<
			mp::contains<Pack2, T>::value,
			relative_complement<Pack1<Ts...>::type, Pack2>::type,
			mp::concatenate<
				Pack1<T>,
				relative_complement<Pack1<Ts...>, Pack2>::type
			>::type
		>::type
	>
{};

} // mp
} // psin

#endif // RELATIVE_COMPLEMENT_HPP
