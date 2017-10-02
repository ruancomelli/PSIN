#ifndef TYPE_COLLECTION_HPP
#define TYPE_COLLECTION_HPP

// UtilsLib
#include <mp/type_collection.tpp>
#include <mp/type_list.hpp>
#include <mp/make_unique_type_list.hpp>

namespace psin {
namespace mp {

template<typename...Ts>
struct type_collection
{
	using identity = type_collection<Ts...>;

	using equivalent_type_list = make_unique_type_list<Ts...>;

	template<typename ... Us>
	constexpr static bool contains = equivalent_type_list::template contains<Us...>;

	constexpr static bool is_empty = equivalent_type_list::is_empty;

	constexpr static unsigned length = equivalent_type_list::length;

	template<typename U>
	constexpr static bool is_superset_of = detail::is_superset_of<identity, U>::value;

	template<typename U>
	constexpr static bool is_subset_of = detail::is_subset_of<identity, U>::value;

	template<typename U>
	constexpr static bool is_equal_to = is_superset_of<U> and is_subset_of<U>;

	template<template<typename...> class ClassToSpecialize>
	using specialize = typename equivalent_type_list::template specialize<ClassToSpecialize>;
};

} // mp
} // psin

#endif