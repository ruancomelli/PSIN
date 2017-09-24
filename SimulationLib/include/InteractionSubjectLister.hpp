#ifndef INTERACTION_SUBJECT_LISTER_HPP
#define INTERACTION_SUBJECT_LISTER_HPP

#include <InteractionSubjectLister.tpp>

namespace psin {

class InteractionSubjectLister
{
public:
	template<typename Interactions, typename Subjects>
	struct generate_combinations : detail::generate_combinations<Interactions, Subjects>
	{};
};

} // psin

#endif