#ifndef REVERT_HPP
#define REVERT_HPP

// UtilsLib
#include <mp/concatenate.hpp>
#include <mp/metafunction.hpp>

namespace psin {
namespace mp {

template<typename T>
struct revert;

template<
	template<typename...> class TypeList,
	typename T,
	typename...Ts
>
struct revert<
	TypeList<T, Ts...>
>
	: mp::metafunction<
		typename mp::concatenate<
			typename revert< TypeList<Ts...> >::type,
			TypeList<T>
		>::type
	>
{};

template<
	template<typename...> class TypeList
>
struct revert< TypeList<> >
	: mp::metafunction< TypeList<> >
{};

} // mp
} // psin

#endif // REVERT_HPP
