#ifndef TYPE_IS_IN_LIST_H
#define TYPE_IS_IN_LIST_H

#include <type_traits>

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
	constexpr static bool value = std::is_same<T,U>::value || type_is_in_list<T, Ts...>::value;
};

#endif
