#ifndef TYPE_LIST_TPP
#define TYPE_LIST_TPP

// UtilsLib
#include <mp/bool_constant.hpp>

// Standard
#include <type_traits>

namespace psin {
namespace mp {

template<typename...Ts>
struct type_list;

namespace detail
{

template<typename ... Ts>
struct is_empty : std::false_type {};

template<>
struct is_empty<> : std::true_type {};


template<typename T, typename...Us>
struct append;

template<typename...Ts, typename...Us>
struct append< mp::type_list<Ts...>, Us...>
	: mp::metafunction< mp::type_list<Ts..., Us...> >
{};


template<typename TypeList, typename...Ts>
struct append_if_new_types;

template<typename TypeList>
struct append_if_new_types<TypeList>
	: mp::metafunction< TypeList >
{};

template<typename TypeList, typename U, typename...Us>
struct append_if_new_types<TypeList, U, Us...>
{
	using type = typename std::conditional<
		!(mp::contains<TypeList, U>::value),
		typename append_if_new_types<
			typename append<TypeList, U>::type, 
			Us... 
		>::type,
		typename append_if_new_types<
			TypeList, 
			Us... 
		>::type
	>::type;
};

template<typename U>
struct has_repeated_types;

template<typename T, typename ... Ts>
struct has_repeated_types< mp::type_list<T, Ts...> >
	: mp::bool_constant< has_repeated_types< mp::type_list<Ts...> >::value or mp::contains<mp::type_list<Ts...>, T>::value >
{};

template<>
struct has_repeated_types< mp::type_list<> > 
	: std::false_type
{};

// template<typename T, typename U>
// struct is_permutation
// 	: std::conditional<
// 		is_superlist_of<T,U>::value and is_superlist_of<U,T>::value,
// 		std::true_type,
// 		std::false_type
// 	>::type
// {};
	
} // detail
} // mp
} // psin

#endif