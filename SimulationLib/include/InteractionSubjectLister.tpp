#ifndef INTERACTION_SUBJECT_LISTER_TPP
#define INTERACTION_SUBJECT_LISTER_TPP

// UtilsLib
#include <metaprogramming.hpp>

namespace psin {
namespace detail {
	
template<typename Interactions, typename Subjects>
struct generate_triplets
	: mp::combinatory::generate_combination_list<Interactions, Subjects, Subjects>
{};


template<typename Triplet>
struct is_valid_triplet
	: mp::bool_constant<
		Triplet::template get<0>::template check<
			typename Triplet::template get<1>,
			typename Triplet::template get<2>
		>::value
	>
{};

template<typename CombinationList>
struct get_valid_triplets
	: mp::metafunction<
		typename mp::purge<
			CombinationList,
			is_valid_triplet
		>::type
	>
{};

template<typename T>
struct permutation_purger
{
	template<typename U>
	struct apply
		: mp::bool_constant< !mp::is_permutation<T, U>::value >
	{};
};

template<typename CombinationList>
struct remove_permutations;

template<template<typename...> class CombinationList, typename T, typename...Ts>
struct remove_permutations<CombinationList<T,Ts...>>
	: mp::metafunction<
		typename mp::concatenate<
			CombinationList<T>,
			typename remove_permutations<
				typename mp::purge<
					CombinationList<Ts...>,
					permutation_purger<T>::template apply
				>::type
			>::type
		>::type
	>
{};

template<template<typename...> class CombinationList>
struct remove_permutations<CombinationList<>>
	: mp::metafunction<CombinationList<>>
{};

template<typename Interactions, typename Subjects>
struct generate_combinations
	: remove_permutations<
		typename get_valid_triplets<
			typename generate_triplets<Interactions, Subjects>::type
		>::type
	>
{};

} // detail
} // psin

#endif