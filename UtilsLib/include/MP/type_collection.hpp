#ifndef TYPE_COLLECTION_HPP
#define TYPE_COLLECTION_HPP

// UtilsLib
#include <MP/type_collection.tpp>
#include <MP/type_list.hpp>
#include <MP/make_unique_type_list.hpp>

template<typename...Ts>
struct type_collection
{
	using identity = type_collection<Ts...>;

	using equivalent_type_list = make_unique_type_list<Ts...>;

	template<typename U, typename ... Us>
	constexpr static bool contains = equivalent_type_list::template contains<U, Us...>;

	constexpr static bool is_empty = equivalent_type_list::is_empty;

	constexpr static unsigned size = equivalent_type_list::size;

	template<typename U>
	constexpr static bool is_superset_of = traits::is_superset_of<identity, U>::value;

	template<typename U>
	constexpr static bool is_subset_of = traits::is_subset_of<identity, U>::value;

	template<typename U>
	constexpr static bool is_equal_to = is_superset_of<U> && is_subset_of<U>;

	template<template<typename...> class ClassToSpecialize>
	using specialize = typename equivalent_type_list::template specialize<ClassToSpecialize>;
};

#endif