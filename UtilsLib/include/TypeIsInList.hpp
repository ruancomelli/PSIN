#ifndef UTILS_TYPE_IS_IN_LIST_H
#define UTILS_TYPE_IS_IN_LIST_H

#include <UniqueTypeList.hpp>

template<typename ... Ts>
struct type_is_in_list;

template<typename T, typename ... Ts>
struct type_is_in_list<T, Ts...>
{
	constexpr static bool value = !is_unique_type_in_list<T, Ts...>::value;
};

#endif //UTILS_TYPE_IS_IN_LIST_H
