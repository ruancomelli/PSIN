#ifndef TYPE_LIST_TRAITS_HPP
#define TYPE_LIST_TRAITS_HPP

#include <type_traits>

template<typename...Ts>
struct type_list;

namespace type_list_traits
{
	template<typename TypeList, typename...ContainedTypes>
	struct contains;

	template<typename TypeList>
	struct contains<TypeList> : std::true_type {};

	template<typename U>
	struct contains<type_list<>, U> : std::false_type {};

	template<typename T, typename...Ts, typename U>
	struct contains<type_list<T, Ts...>, U>
		: std::conditional<
			std::is_same<T, U>::value || contains<type_list<Ts...>, U>::value,
			std::true_type,
			std::false_type
		>::type
	{};

	template<typename TypeList, typename U, typename...Us>
	struct contains<TypeList, U, Us...>
		: std::conditional<
			contains<TypeList, U>::value || contains<TypeList, Us...>::value,
			std::true_type,
			std::false_type
		>::type
	{};



	template<typename ... Ts>
	struct is_empty : std::false_type {};

	template<>
	struct is_empty<> : std::true_type {};



	template<typename ... Ts>
	struct size;
	
	template<typename T, typename ... Ts>
	struct size<T, Ts...>
	{
		constexpr static unsigned value = 1 + size<Ts...>::value;
	};
	
	template<>
	struct size<>
	{
		constexpr static unsigned value = 0;
	};


	template<typename T, typename...Us>
	struct append;

	template<typename...Ts, typename...Us>
	struct append<type_list<Ts...>, Us...>
	{
		using type = type_list<Ts..., Us...>;	
	};



	template<typename TypeList, typename...Ts>
	struct append_if_new_types;

	template<typename TypeList>
	struct append_if_new_types<TypeList>
	{
		using type = TypeList;
	};

	template<typename TypeList, typename U, typename...Us>
	struct append_if_new_types<TypeList, U, Us...>
	{
		using type = typename std::conditional<
			!(contains<TypeList, U>::value),
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

	template<typename ... Ts>
	struct has_repeated_types;

	template<typename T, typename ... Ts>
	struct has_repeated_types<T, Ts...>
		: std::conditional<
			has_repeated_types<Ts...>::value || contains<type_list<Ts...>, T>::value,
			std::true_type,
			std::false_type
		>::type
	{};

	template<>
	struct has_repeated_types<> : std::false_type {};


	template<typename T, typename U>
	struct is_superlist_of;

	template<typename...Ts, typename...Us>
	struct is_superlist_of<type_list<Ts...>, type_list<Us...> >
		: std::conditional<
			contains<type_list<Ts...>, Us...>::value,
			std::true_type,
			std::false_type
		>::type
	{};


	template<typename T, typename U>
	using is_sublist_of = is_superlist_of<U, T>;


	template<typename T, typename U>
	struct is_permutation
		: std::conditional<
			is_superlist_of<T,U>::value && is_superlist_of<U,T>::value,
			std::true_type,
			std::false_type
		>::type
	{};
}

#endif