#ifndef COMBINATORY_TPP
#define COMBINATORY_TPP

// UtilsLib
#include <MP/concatenate.hpp>
#include <MP/get.hpp>
#include <MP/length.hpp>
#include <MP/type_list.hpp>

// Standard
#include <utility>
#include <type_traits>

namespace traits {
	template<size_t S = 0, size_t Value = 0>
	struct make_constant_index_sequence;

	template<size_t S, size_t Value>
	struct make_constant_index_sequence<S, Value>
		: concatenate< index_sequence<Value>, make_constant_index_sequence<S-1, Value> >::type
	{};

	template<size_t Value>
	struct make_constant_index_sequence<0, Value>
		: std::index_sequence<>
	{};


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


	template<typename...TypeLists>
	struct index_limit
		: metafunction< std::index_sequence< length<TypeLists>... > >
	{};

	template<typename...TypeLists>
	struct last_combination_indexes
		: metafunction< std::index_sequence< length<TypeLists> - 1... > >
	{};


	template<typename Indexes, typename...TypeLists>
	struct get_combination;

	template<std::size_t...Is, typename...TLs>
	struct get_combination< std::index_sequence<Is...>, TLs... >
		: metafunction< type_list< typename get<Is, TLs> ... > >
	{};





	template<typename...TypeLists>
	struct generate_list;

	template<>
	struct generate_list<>
		: metafunction< type_list<> >
	{};

	template<typename T, typename...Ts, typename...TypeLists>
	struct generate_list<type_list<T, Ts...>, TypeLists...>
	{
		// To implement	
	};



} // traits

#endif // COMBINATORY_TPP
