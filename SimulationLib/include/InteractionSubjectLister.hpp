#ifndef INTERACTION_SUBJECT_LISTER_HPP
#define INTERACTION_SUBJECT_LISTER_HPP

// UtilsLib
#include <metaprogramming.hpp>

template<typename T>
struct check_interaction_subject : std::false_type
{};

template<typename I, typename S1, typename S2>
struct check_interaction_subject< type_list<I, S1, S2> >
	: bool_type< I::template check<S1,S2>::value >
{};

class InteractionSubjectLister
{
	template<typename Interactions, typename Subjects>
	using generate_combinations = typename combinatory::generate_combination_list<Interactions, Subjects, Subjects>;

	template<typename Interactions, typename Subjects>
	using generate_purged_combinations = typename mp::purge::apply< 
		generate_combinations<Interactions, Subjects>::type,
		check_interaction_subject
	>;
};

#endif