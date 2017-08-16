#ifndef INTERACTION_SUBJECT_LISTER_HPP
#define INTERACTION_SUBJECT_LISTER_HPP

// SimulationLib
#include <MP/InteractionSubjectLister.hpp>

// UtilsLib
#include <metaprogramming.hpp>

class InteractionSubjectLister
{
	template<typename Interactions, typename Subjects>
	using generate_pairs = typename mp::generate_pairs<Interactions, Subjects>::type;

	template<typename Interactions, typename Subjects>
	using list = typename mp::generate_pairs<Interactions, Subjects>::type;
};

#endif