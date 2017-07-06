#ifndef TYPE_LIST_HPP
#define TYPE_LIST_HPP

template<typename...Ts>
struct type_list;

namespace traits
{
	template<typename U, typename ... Us>
	struct contains<type_list<>, U, Us...>
	{
		constexpr bool value = false;
	}
	
	template<typename U, typename ... Us>
	struct contains<type_list<>, U, Us...>
	{
		constexpr bool value = false;
	}
};

template<typename...Ts>
struct type_list
{
	template<typename T>
	using append = type_list<Ts..., T>;

	template<typename T>
	using prepend = type_list<T, Ts...>;

	template<typename U, typename ... Us>
	constexpr bool contains = traits::contains<type_list<Ts...>, U, Us...>::value;
};

#endif

// WARNING: The use of this is, e.g., 'static_assert( std::is_same< type_list<int>::append<double> , type_list<int, double> >::value );'
// That is, 'type_list<Ts...>::append<T>' is the same as 'type_list<Ts..., T>'.
// The problem is that, in 'std::' syntax, there is a 'type', as in
// 		std::conditional<true, int, double>::type;
// Should we change our code? If so, this would change a lot the 'type_list', and the implementation would be more polluted.