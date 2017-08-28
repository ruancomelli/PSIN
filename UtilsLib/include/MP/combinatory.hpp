#ifndef COMBINATORY_HPP
#define COMBINATORY_HPP

#include <mp/combinatory.tpp>

namespace psin {
namespace mp {

struct combinatory
{
	template<typename IndexSequence, typename...TypeLists>
	using get_combination = detail::get_combination<IndexSequence, TypeLists...>;

	template<typename...TypeLists>
	using generate_combination_list = detail::generate_list<TypeLists...>;
};

} // mp
} // psin

#endif // COMBINATORY_HPP
