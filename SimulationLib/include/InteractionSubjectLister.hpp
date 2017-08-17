#ifndef INTERACTION_SUBJECT_LISTER_HPP
#define INTERACTION_SUBJECT_LISTER_HPP

// UtilsLib
#include <metaprogramming.hpp>

class InteractionSubjectLister
{
	template<typename Interactions, typename Subjects>
	using generate_combinations = typename mp::generate_combinations<Interactions, Subjects>::type;

	template<typename>
};

#endif