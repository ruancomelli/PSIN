#ifndef UTILS_TYPE_LIST_HPP
#define UTILS_TYPE_LIST_HPP

template<typename...Ts>
struct type_list;

template<typename T, typename U>
struct prepend_type_to_type_list;

template<typename T, typename...Ts>
struct prepend_type_to_type_list<T, type_list<Ts...>>
{
	using value = type_list<T, Ts...>;
};

template<typename T, typename U>
struct append_type_to_type_list;

template<typename T, typename...Ts>
struct append_type_to_type_list<T, type_list<Ts...>>
{
	using value = type_list<Ts..., T>;
};


#endif
