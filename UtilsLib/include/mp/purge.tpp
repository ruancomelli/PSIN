#ifndef PURGE_TPP
#define PURGE_TPP

// UtilsLib
#include <mp/concatenate.hpp>
#include <mp/metafunction.hpp>

namespace psin {
namespace mp {
namespace detail {

template<typename TypeList, template<typename> class CheckMF>
struct purge_apply;

template<template<typename...> class TypeList, template<typename> class CheckMF>
struct purge_apply<TypeList<>, CheckMF> : mp::metafunction< TypeList<> >
{};

template<template<typename...> class TypeList, template<typename> class CheckMF, typename T, typename...Ts>
struct purge_apply<TypeList<T, Ts...>, CheckMF>
	: mp::metafunction<
		typename mp::concatenate<
			typename std::conditional<
				CheckMF<T>::value,
				TypeList<T>,
				TypeList<>
			>::type,
			typename purge_apply<TypeList<Ts...>, CheckMF>::type
		>::type
	>
{};

} // detail
} // mp
} // psin

#endif // PURGE_TPP
