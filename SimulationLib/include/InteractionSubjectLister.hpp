#ifndef INTERACTION_SUBJECT_LISTER_HPP
#define INTERACTION_SUBJECT_LISTER_HPP

#include <InteractionSubjectLister.tpp>

namespace psin {
	
template<typename T>
struct interaction_check_subjects : std::false_type
{};

template<typename I, typename S1, typename S2>
struct interaction_check_subjects< mp::type_list<I, S1, S2> >
	: mp::bool_constant< I::template check<S1,S2>::value >
{};

class InteractionSubjectLister
{
public:
	template<typename Interactions, typename Subjects>
	struct generate_combinations : detail::generate_combinations<Interactions, Subjects>
	{};
};

} // psin

#endif