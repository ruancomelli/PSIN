#ifndef TYPE_COLLECTION_TRAITS_HPP
#define TYPE_COLLECTION_TRAITS_HPP

// UtilsLib
#include <Metaprogramming/type_list.hpp>

// Standard
#include <type_traits>

template<typename...Ts>
struct type_collection;

namespace traits
{
	template<typename T, typename U>
	struct is_superset_of;

	template<typename...Ts>
	struct is_superset_of< type_collection<Ts...>,  type_collection<> >
		: std::true_type
	{};

	template<typename...Ts, typename U, typename...Us>
	struct is_superset_of< type_collection<Ts...>,  type_collection<U, Us...> >
		: std::conditional<
			type_list<Ts...>::template contains<U, Us...>,
			std::true_type,
			std::false_type
		>::type
	{};

	template<typename T, typename U>
	using is_subset_of = is_superset_of<U, T>;
}

#endif