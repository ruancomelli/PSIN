#ifndef COMBINATORY_TPP
#define COMBINATORY_TPP

// UtilsLib
#include <mp/none_of.hpp>
#include <mp/concatenate.hpp>
#include <mp/get.hpp>
#include <mp/is_empty.hpp>
#include <mp/length.hpp>
#include <mp/metafunction.hpp>
#include <mp/type_list.hpp>

// Standard
#include <utility>
#include <type_traits>

namespace psin {
namespace mp {
namespace detail {
	
template<std::size_t S = 0, std::size_t Value = 0>
struct make_constant_index_sequence
	: mp::metafunction< 
		typename mp::concatenate< 
			std::index_sequence<Value>, 
			typename make_constant_index_sequence<S-1, Value>::type 
		>::type 
	>
{};

template<std::size_t Value>
struct make_constant_index_sequence<0, Value>
	: mp::metafunction< std::index_sequence<> >
{};


template<typename Indexes, typename Limits>
struct format_indexes_based_on_limits;

template<template<std::size_t...> class List>
struct format_indexes_based_on_limits<
	List<>,
	List<>
> : mp::metafunction< List<> >
{
	constexpr static std::size_t remainder = 0;
};

template<typename T, template<typename, T...> class List>
struct format_indexes_based_on_limits<
	List<T>,
	List<T>
> : mp::metafunction< List<T> >
{
	constexpr static T remainder = 0;
};

template<template<std::size_t...> class List, 
	std::size_t I, 
	std::size_t L>
struct format_indexes_based_on_limits<
	List<I>,
	List<L>
> : mp::metafunction< List<I%L> >
{
	constexpr static std::size_t remainder = I/L;
};

template<typename T, template<typename, T...> class List, T I, T L>
struct format_indexes_based_on_limits<
	List<T, I>,
	List<T, L>
> : mp::metafunction< List<T, I%L> >
{
	constexpr static T remainder = I/L;
};

template<template<std::size_t...> class List, 
	std::size_t I1, std::size_t I2, std::size_t...Is, 
	std::size_t L1, std::size_t L2, std::size_t...Ls>
struct format_indexes_based_on_limits<
	List<I1, I2, Is...>,
	List<L1, L2, Ls...>
> : mp::metafunction<
		typename mp::concatenate< 
			List<I1%L1>,
			typename format_indexes_based_on_limits<
				List<I2 + I1/L1, Is...>,
				List<L2, Ls...>
			>::type
		>::type 
	>
{
	constexpr static std::size_t remainder = format_indexes_based_on_limits<
			List<I2 + I1/L1, Is...>,
			List<L2, Ls...>
		>::remainder; 
};

template<typename T, template<typename, T...> class List, 
	T I1, T I2, T...Is, 
	T L1, T L2, T...Ls>
struct format_indexes_based_on_limits<
	List<T, I1, I2, Is...>,
	List<T, L1, L2, Ls...>
> : mp::metafunction<
		typename mp::concatenate< 
			List<T, I1%L1>,
			typename format_indexes_based_on_limits<
				List<T, I2 + I1/L1, Is...>,
				List<T, L2, Ls...>
			>::type
		>::type 
	>
{
	constexpr static T remainder = format_indexes_based_on_limits<
			List<T, I2 + I1/L1, Is...>,
			List<T, L2, Ls...>
		>::remainder; 
};


template<typename...TypeLists>
struct index_limit
	: mp::metafunction< std::index_sequence< mp::length<TypeLists>::value ... > >
{};

template<typename...TypeLists>
struct last_combination_indexes
	: mp::metafunction< std::index_sequence< mp::length<TypeLists>::value - 1 ... > >
{};

template<typename Indexes, typename Limits>
struct next_combination_indexes;

template<std::size_t I, std::size_t...Is, typename Limits>
struct next_combination_indexes< std::index_sequence<I, Is...>, Limits >
	: format_indexes_based_on_limits< 
		std::index_sequence<I+1, Is...>,
		Limits
	>
{};


template<typename Indexes, typename...TypeLists>
struct get_combination;

template<std::size_t...Is, typename...TLs>
struct get_combination< std::index_sequence<Is...>, TLs... >
	: mp::metafunction< mp::type_list< typename mp::get<Is, TLs>::type ... > >
{};



template<typename Indexes, typename...TLs>
struct iterate_generate_list
	: mp::metafunction<
		typename mp::concatenate<
			mp::type_list<typename get_combination<Indexes, TLs...>::type>,
			typename iterate_generate_list<
				typename next_combination_indexes<Indexes, typename index_limit<TLs...>::type>::type, 
				TLs...
			>::type
		>::type
	>
{};

template<typename...TLs>
struct iterate_generate_list<
	typename last_combination_indexes<TLs...>::type,
	TLs...
>
	: mp::metafunction<	
		mp::type_list<
			typename get_combination<
				typename last_combination_indexes<TLs...>::type, 
				TLs...
			>::type
		>
	>
{};

template<typename...TLs>
struct non_empty_types
	: mp::none_of<
		type_list<TLs...>,
		is_empty
	>
{};

template<bool iterate, typename...TypeLists>
struct generate_list
	: iterate_generate_list<
		typename make_constant_index_sequence<sizeof...(TypeLists), 0>::type, 
		TypeLists...
	>
{};

template<typename...TypeLists>
struct generate_list<false, TypeLists...>
	: mp::metafunction<
		type_list<>
	>
{};

} // detail
} // mp
} // psin

#endif // COMBINATORY_TPP
