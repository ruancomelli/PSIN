#ifndef INSERT_NEW_TYPES_INTO_TYPE_LIST_HPP
#define INSERT_NEW_TYPES_INTO_TYPE_LIST_HPP

// UtilsLib
#include <type_is_in_list.hpp>
#include <type_list.hpp>

// Standard
#include <type_traits>

template<typename T, typename...Ts>
struct insert_new_types_into_type_list;

template<typename...Ts, typename T, typename...Us>
struct insert_new_types_into_type_list<type_list<Ts...>, T, Us...>
{
	using value = typename std::conditional<
			!type_is_in_list<T, Ts...>::value,
			typename insert_new_types_into_type_list<
				type_list<Ts..., T>,
				Us...
			>::value,
			typename insert_new_types_into_type_list<
				type_list<Ts...>,
				Us...
			>::value
		>::type;
};

template<typename...Ts>
struct insert_new_types_into_type_list<type_list<Ts...>>
{
	using value = type_list<Ts...>;
};


#endif
