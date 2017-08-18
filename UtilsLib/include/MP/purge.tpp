#ifndef PURGE_TPP
#define PURGE_TPP

// UtilsLib
#include <MP/concatenate.hpp>
#include <MP/metafunction.hpp>

namespace traits {
	template<typename TypeList, template<typename> class CheckMF>
	struct purge_apply;

	template<template<typename...> class TypeList, template<typename> class CheckMF>
	struct purge_apply<TypeList<>, CheckMF> : metafunction< TypeList<> >
	{};

	template<template<typename...> class TypeList, template<typename> class CheckMF, typename T, typename...Ts>
	struct purge_apply<TypeList<T, Ts...>, CheckMF>
		: metafunction<
			typename concatenate<
				typename std::conditional<
					CheckMF<T>::value,
					TypeList<T>,
					TypeList<>
				>::type,
				typename purge_apply<TypeList<Ts...>, CheckMF>::type
			>::type
		>
	{};
} // traits

#endif // PURGE_TPP
