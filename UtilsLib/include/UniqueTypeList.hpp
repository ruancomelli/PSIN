#ifndef UTILS_UNIQUE_TYPE_LIST_HPP
#define UTILS_UNIQUE_TYPE_LIST_HPP


#include <IfThenElse.hpp>
#include <TypeIsInList.hpp>
#include <TypeList.hpp>
#include <IsUniqueTypeInList.hpp>


// ---- is_unique_type_list ----
template<typename ... Ts>
struct is_unique_type_list;

template<typename T, typename ... Ts>
struct is_unique_type_list<T, Ts...>
{
	constexpr static bool value = is_unique_type_list<Ts...>::value && is_unique_type_in_list<T, Ts...>::value;
};

template<>
struct is_unique_type_list<>
{
	constexpr static bool value = true;
};

// ---- unique_type_list ----
template<typename ... RepeatedArgs>
struct unique_type_list;

template<typename T, typename...Ts>
struct unique_type_list<T, Ts...>
{
	using value = typename if_then_else<
			type_is_in_list<T, Ts...>::value,
			typename unique_type_list<Ts...>::value,
			prepend_type_to_type_list<T, typename unique_type_list<Ts...>::value>
		>::value;
};

template<typename T>
struct unique_type_list<T>
{
	using value = type_list<T>;
};


#endif
