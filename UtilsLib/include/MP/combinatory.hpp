#ifndef COMBINATORY_HPP
#define COMBINATORY_HPP

#include <MP/combinatory.tpp>

struct combinatory
{
	template<typename IndexSequence, typename...TypeLists>
	using get_combination = traits::get_combination<IndexSequence, TypeLists...>;

	template<typename...TypeLists>
	using generate_list = traits::generate_list<TypeLists...>;
};

#endif // COMBINATORY_HPP
