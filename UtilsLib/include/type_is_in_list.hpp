#ifndef UTILS_TYPE_IS_IN_LIST_H
#define UTILS_TYPE_IS_IN_LIST_H


#include <equal_types.hpp>



template<typename T, typename ... Ts>
struct type_is_in_list;

template<typename T>
struct type_is_in_list<T>
{
	constexpr static bool value = false;
};

template<typename T, typename U, typename ... Ts>
struct type_is_in_list<T, U, Ts...>
{
	constexpr static bool value = equal_types<T,U>::value || type_is_in_list<T, Ts...>::value;
};

#endif
