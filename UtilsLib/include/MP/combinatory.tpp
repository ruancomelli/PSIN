#ifndef COMBINATORY_TPP
#define COMBINATORY_TPP

// UtilsLib
#include <MP/concatenate.hpp>
#include <MP/length.hpp>
#include <MP/type_list.hpp>

// Standard
#include <type_traits>

namespace traits {
	template<typename...TypeLists>
	struct generate_list;

	template<>
	struct generate_list<>
	{
		using type = type_list<>;
	};

	template<typename T, typename...Ts, typename...TypeLists>
	struct generate_list<type_list<T, Ts...>, TypeLists...>
	{
		
	};


	template<typename Indexes, typename...TypeLists>
	struct get_combination;

	template<std::size_t...Is, typename...TLs>
	struct get_combination< std::index_sequence<Is...>, TLs... >
	{
		using type = type_list< typename TLs::template get<Is> ... >;
	};





	template<typename Indexes, typename Limits>
	struct format_indexes_based_on_limits;

	template<template<std::size_t...> class List>
	struct format_indexes_based_on_limits<
		List<>,
		List<>
	> : metafunction< List<> >,
		std::integral_constant<size_t, 0>
	{};

	template<template<std::size_t...> class List, 
		std::size_t I, 
		std::size_t L>
	struct format_indexes_based_on_limits<
		List<I>,
		List<L>
	> : metafunction< List<I%L> >,
		std::integral_constant<size_t, I/L>
	{};

	template<template<std::size_t...> class List, 
		std::size_t I1, std::size_t I2, std::size_t...Is, 
		std::size_t L1, std::size_t L2, std::size_t...Ls>
	struct format_indexes_based_on_limits<
		List<I1, I2, Is...>,
		List<L1, L2, Ls...>
	> : metafunction<
			typename concatenate< 
				List<I1%L1>,
				typename format_indexes_based_on_limits<
					List<I2 + I1/L1, Is...>,
					List<L2, Ls...>
				>::type
			>::type 
		>,
		std::integral_constant<
			size_t,
			format_indexes_based_on_limits<
				List<I2 + I1/L1, Is...>,
				List<L2, Ls...>
			>::value 
		>
	{};


	template<typename Indexes, typename...TypeLists>
	struct next_combination_indexes;

	template<std::size_t I, std::size_t...Is, typename...TLs>
	struct next_combination_indexes< std::index_sequence<I, Is...>, TLs... >
		: format_indexes_based_on_limits< 
			std::index_sequence<I+1, Is...>,
			std::index_sequence<length<TLs>::value...>
		>
	{};
} // traits

#endif // COMBINATORY_TPP
