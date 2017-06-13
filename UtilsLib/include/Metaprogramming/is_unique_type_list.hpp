#ifndef UTILS_IS_UNIQUE_TYPE_LIST_HPP
#define UTILS_IS_UNIQUE_TYPE_LIST_HPP


#include <Metaprogramming/type_is_in_list.hpp>


// ---- is_unique_type_list ----
template<typename ... Ts>
struct is_unique_type_list;

template<typename T, typename ... Ts>
struct is_unique_type_list<T, Ts...>
{
	constexpr static bool value = is_unique_type_list<Ts...>::value && !type_is_in_list<T, Ts...>::value;
};

template<>
struct is_unique_type_list<>
{
	constexpr static bool value = true;
};


#endif
