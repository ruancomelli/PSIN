#ifndef INTERACTION_SUBJECT_LISTER_TPP
#define INTERACTION_SUBJECT_LISTER_TPP

// UtilsLib
#include <metaprogramming.hpp>

namespace traits {
	template<typename Interactions, typename Subjects>
	struct generate_triplets
		: combinatory::generate_combination_list<Interactions, Subjects, Subjects>
	{};


	template<typename Triplet>
	struct is_valid_triplet
		: bool_type<
			Triplet::template get<0>::template check<
				typename Triplet::template get<1>,
				typename Triplet::template get<2>
			>::value
		>
	{};

	template<typename CombinationList>
	struct get_valid_triplets
		: metafunction<
			typename mp::purge::apply<
				CombinationList,
				is_valid_triplet
			>::type
		>
	{};

	template<typename Interactions, typename Subjects>
	struct generate_combinations
		: metafunction<
			typename get_valid_triplets<
				typename generate_triplets<Interactions, Subjects>::type
			>::type
		>
	{};
} // traits

#endif