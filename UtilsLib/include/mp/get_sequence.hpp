#ifndef GET_SEQUENCE_HPP
#define GET_SEQUENCE_HPP

#include <mp/concatenate.hpp>
#include <mp/get.hpp>
#include <mp/metafunction.hpp>

namespace psin {
namespace mp {

template<typename Indices, typename TypeList>
struct get_sequence;

template<typename T, template<typename, T...> class IndexSequence, typename TypeList>
struct get_sequence< IndexSequence<T>, TypeList >
	: mp::metafunction<
		type_list<>
	>
{};

template<typename T, template<typename, T...> class IndexSequence, T I, T...Is, typename TypeList>
struct get_sequence< IndexSequence<T, I, Is...>, TypeList >
	: mp::metafunction<
		typename mp::concatenate<
			type_list< typename mp::get<I, TypeList>::type >,
			typename get_sequence<
				IndexSequence<T, Is...>,
				TypeList
			>::type
		>::type
	>
{};

} // mp
} // psin

#endif // GET_SEQUENCE_HPP
