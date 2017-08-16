#ifndef INTERACTION_SUBJECT_LISTER_HPP
#define INTERACTION_SUBJECT_LISTER_HPP

// SimulationLib
#include <MP/InteractionSubjectLister.hpp>

// UtilsLib
#include <metaprogramming.hpp>

class InteractionSubjectLister
{
	template<typename Interactions, typename Subjects>
	using generate_pairs = mp::generate_pairs<Interactions, Subjects>::type;
};

#endif