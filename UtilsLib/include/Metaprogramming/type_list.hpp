#ifndef TYPE_LIST_HPP
#define TYPE_LIST_HPP

#include <type_traits>

#include <Metaprogramming/traits/type_list_traits.hpp>

template<typename...Ts>
struct type_list
{
	template<typename ... Us>
	using append = type_list<Ts..., Us...>;

	template<typename...Us>
	using append_if_new_types = typename type_list_traits::append_if_new_types<type_list<Ts...>, Us...>::type;

	template<typename ... Us>
	using prepend = type_list<Us..., Ts...>;

	template<typename U, typename ... Us>
	constexpr static bool contains = type_list_traits::contains<type_list<Ts...>, U, Us...>::value;

	constexpr static bool is_empty = type_list_traits::is_empty<Ts...>::value;

	constexpr static bool has_repeated_types = type_list_traits::has_repeated_types<Ts...>::value;

	// using remove_repeated_types = type_list<>::append_if_new_types<Ts...>;

	constexpr static unsigned count = type_list_traits::count<Ts...>::value;
};

#endif

// WARNING: The use of this is, e.g., 'static_assert( std::is_same< type_list<int>::append<double> , type_list<int, double> >::value );'
// That is, 'type_list<Ts...>::append<T>' is the same as 'type_list<Ts..., T>'.
// The problem is that, in 'std::' syntax, there is a 'type', as in
// 		std::conditional<true, int, double>::type;
// Should we change our code? If so, this would change a lot the 'type_list', and the implementation would be more polluted.