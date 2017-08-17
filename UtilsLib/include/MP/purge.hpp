#ifndef PURGE_HPP
#define PURGE_HPP

// UtilsLib
#include <MP/concatenate.hpp>
#include <MP/metafunction.hpp>
#include <MP/type_list.hpp>

namespace mp {
	struct purge
	{
		template<template<typename> class CheckMF, typename...Ts>
		struct apply;

		template<template<typename> class CheckMF>
		struct apply<CheckMF> : metafunction< type_list<> >
		{};

		template<template<typename> class CheckMF, typename T, typename...Ts>
		struct apply<CheckMF, T, Ts...>
			: metafunction<
				typename concatenate<
					typename std::conditional<
						CheckMF<T>::value,
						type_list<T>,
						type_list<>
					>::type,
					typename apply<CheckMF, Ts...>::type
				>::type
			>
		{};
	};
} // mp

#endif // PURGE_HPP
