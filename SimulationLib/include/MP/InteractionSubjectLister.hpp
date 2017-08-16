#ifndef MP_INTERACTION_SUBJECT_LISTER_HPP
#define MP_INTERACTION_SUBJECT_LISTER_HPP

#include <MP/type_list.hpp>

namespace mp {
	template<typename T, typename U>
	using type_pair = type_list<T, U>;

	template<typename Interactions, typename Subjects>
	struct generate_pairs;

	template<typename I, typename...Is, typename Subjects>
	struct generate_pairs<
		type_list<I, Is...>,
		Subjects
	>
	{
		using blah = typename generate_pairs<I, Subjects>::type;
		using foo = typename generate_pairs<Is..., Subjects>::type;
		using type = typename blah::template concatenate< 
			foo
		>;
	};

	template<typename I, typename S, typename...Ss>
	struct generate_pairs<
		type_list<I>,
		type_list<S, Ss...>
	>
	{
		using type = typename std::conditional<
			I::template check<S>::value,
			type_list< type_pair<I, S> >,
			type_list<>
		>::type::template concatenate< 
			generate_pairs<I, Ss...>::type
		>;
	};

	template<typename Interactions>
	struct generate_pairs<
		Interactions,
		type_list<>
	>
	{
		using type = type_list<>;
	};

	template<typename Subjects>
	struct generate_pairs<
		type_list<>,
		Subjects
	>
	{
		using type = type_list<>;
	};

} // mp

#endif
