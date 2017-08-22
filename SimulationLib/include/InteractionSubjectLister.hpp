#ifndef INTERACTION_SUBJECT_LISTER_HPP
#define INTERACTION_SUBJECT_LISTER_HPP

#include <InteractionSubjectLister.tpp>

template<typename T>
struct interaction_check_subjects : std::false_type
{};

template<typename I, typename S1, typename S2>
struct interaction_check_subjects< type_list<I, S1, S2> >
	: bool_type< I::template check<S1,S2>::value >
{};

class InteractionSubjectLister
{
public:
	template<typename Interactions, typename Subjects>
	struct generate_combinations : traits::generate_combinations<Interactions, Subjects>
	{};
};


#endif