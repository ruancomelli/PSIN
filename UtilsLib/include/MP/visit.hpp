#ifndef VISIT_HPP
#define VISIT_HPP

// UtilsLib
#include <mp/get.hpp>
#include <mp/length.hpp>

// Standard
#include <cstddef>

namespace psin {
namespace mp {

template<
	typename TypeList,
	template<typename> class Visitor,
	std::size_t Pos = mp::length<TypeList>::value - 1
>
struct visit
{
	static void call()
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call();
		visit< TypeList, Visitor, Pos-1 >::call();
	}
};

template<
	typename TypeList,
	template<typename> class Visitor
>
struct visit<TypeList, Visitor, 0>
{
	static void call()
	{
		Visitor< typename mp::get<0, TypeList>::type >::call();
	}
};

	
} // mp
} // psin

#endif // VISIT_HPP
