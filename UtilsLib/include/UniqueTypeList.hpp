#ifndef UTILS_UNIQUE_TYPE_LIST_H
#define UTILS_UNIQUE_TYPE_LIST_H

// ---- equal_types ----
template<typename T, typename U>
struct equal_types
{
	constexpr static bool value = false;
};

template<typename T>
struct equal_types<T, T>
{
	constexpr static bool value = true;
};

// ---- is_unique_type_in_list ----
template<typename ... Ts>
struct is_unique_type_in_list;

template<typename T, typename U, typename ... Ts>
struct is_unique_type_in_list<T, U, Ts...>
{
	constexpr static bool value = is_unique_type_in_list<T, Ts...>::value && !(equal_types<T, U>::value);
};

template<typename T>
struct is_unique_type_in_list<T>
{
	constexpr static bool value = true;
};


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


// ---- UniqueTypeList ----
template<typename ... Ts>
struct UniqueTypeList
{
	static_assert(is_unique_type_list<Ts...>::value, "UniqueTypeList can only be declared with unique types as template parameters");
};

#endif //UTILS_UNIQUE_TYPE_LIST_H
