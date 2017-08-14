#ifndef TYPE_LIST_TRAITS_HPP
#define TYPE_LIST_TRAITS_HPP

#include <cstddef>
#include <type_traits>

template<typename...Ts>
struct type_list;

namespace traits
{
	template<typename TypeList, typename...ContainedTypes>
	struct contains;

	template<typename TypeList>
	struct contains<TypeList> : std::true_type {};

	template<typename TypeList, typename U, typename...Us>
	struct contains<TypeList, U, Us...>
		: std::conditional<
			contains<TypeList, U>::value && contains<TypeList, Us...>::value,
			std::true_type,
			std::false_type
		>::type
	{};

	template<typename U>
	struct contains< type_list<>, U> : std::false_type {};

	template<typename T, typename...Ts, typename U>
	struct contains< type_list<T, Ts...>, U>
		: std::conditional<
			std::is_same<T, U>::value || contains< type_list<Ts...>, U>::value,
			std::true_type,
			std::false_type
		>::type
	{};



	template<typename ... Ts>
	struct is_empty : std::false_type {};

	template<>
	struct is_empty<> : std::true_type {};



	template<typename T>
	struct size;
	
	template<typename T, typename ... Ts>
	struct size< type_list<T, Ts...> >
	{
		constexpr static std::size_t value = 1 + size< type_list<Ts...> >::value;
	};
	
	template<>
	struct size< type_list<> >
	{
		constexpr static std::size_t value = 0;
	};


	template<typename T, typename...Us>
	struct append;

	template<typename...Ts, typename...Us>
	struct append< type_list<Ts...>, Us...>
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

	template<typename U>
	struct has_repeated_types;

	template<typename T, typename ... Ts>
	struct has_repeated_types< type_list<T, Ts...> >
		: std::conditional<
			has_repeated_types< type_list<Ts...> >::value || contains<type_list<Ts...>, T>::value,
			std::true_type,
			std::false_type
		>::type
	{};

	template<>
	struct has_repeated_types< type_list<> > : std::false_type {};


	template<typename T, typename U>
	struct concatenate;

	template<typename...Ts, typename...Us>
	struct concatenate<
		type_list<Ts...>,
		type_list<Us...>
	>
	{
		using type = type_list<Ts..., Us...>;
	};

	template<typename TypeList, std::size_t position>
	struct get;

	template<typename T, typename...Ts, std::size_t position>
	struct get<
		type_list<T, Ts...>,
		position
	>
	{
		using type = typename get< type_list<Ts...> , position - 1>::type;
	};

	template<typename T, typename...Ts>
	struct get<
		type_list<T, Ts...>,
		0
	>
	{
		using type = T;
	};

	template<std::size_t position>
	struct get<
		type_list<>,
		position
	>
	{
		static_assert( size< type_list<> >::value > position,
			"'position' in 'TypeList::get<position>' must be less than 'TypeList::size' ");

		using type = void;
	};

	// template<std::size_t position>
	// struct get<
	// 	type_list<>,
	// 	position
	// >
	// {
	// 	static_assert(
	// 		type_list<T, Ts...>::size > position,
	// 		"Error: 'position' in expression 'TypeList::get<position>' must be less than 'TypeList::size'");
	// };

	// template<typename T, typename U>
	// struct is_permutation
	// 	: std::conditional<
	// 		is_superlist_of<T,U>::value && is_superlist_of<U,T>::value,
	// 		std::true_type,
	// 		std::false_type
	// 	>::type
	// {};
	
}

#endif