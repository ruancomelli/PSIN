#ifndef INTERACTION_SUBJECT_LISTER_HPP
#define INTERACTION_SUBJECT_LISTER_HPP

#include <InteractionSubjectLister.tpp>

namespace psin {

class InteractionSubjectLister
{
public:
	template<typename Interactions, typename Subjects1, typename Subjects2=Subjects1>
	struct generate_combinations : detail::generate_combinations<Interactions, Subjects1, Subjects2>
	{};
};

} // psin

#endif