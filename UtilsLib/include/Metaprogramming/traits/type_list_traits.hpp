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
	struct contains<TypeList>
	{
		constexpr static bool value = true;
	};

	template<typename U>
	struct contains<type_list<>, U>
	{
		constexpr static bool value = false;
	};

	template<typename T, typename...Ts, typename U>
	struct contains<type_list<T, Ts...>, U>
	{
		constexpr static bool value = std::is_same<T, U>::value || contains<type_list<Ts...>, U>::value;
	};

	template<typename TypeList, typename U, typename...Us>
	struct contains<TypeList, U, Us...>
	{
		constexpr static bool value = contains<TypeList, U>::value || contains<TypeList, Us...>::value;
	};




	template<typename ... Ts>
	struct is_empty
	{
		constexpr static bool value = false;
	};

	template<>
	struct is_empty<>
	{
		constexpr static bool value = true;
	};



	template<typename ... Ts>
	struct count;
	
	template<typename T, typename ... Ts>
	struct count<T, Ts...>
	{
		constexpr static unsigned value = 1 + count<Ts...>::value;
	};
	
	template<>
	struct count<>
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
	{
		constexpr static bool value = has_repeated_types<Ts...>::value || contains<type_list<Ts...>, T>::value;
	};

	template<>
	struct has_repeated_types<>
	{
		constexpr static bool value = false;
	};
}

#endif