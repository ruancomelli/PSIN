#ifndef VISIT_HPP
#define VISIT_HPP

// UtilsLib
#include <mp/get.hpp>
#include <mp/length.hpp>

// Standard
#include <cstddef>
#include <tuple>

namespace psin {
namespace mp {

template<
	typename TypeList,
	template<typename> class Visitor,
	std::size_t Pos = mp::length<TypeList>::value - 1
>
struct visit
{
	template<typename...Tuples>
	static void call( std::tuple<Tuples...> & arg )
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call( std::get<Pos>(arg) );
		visit< TypeList, Visitor, Pos-1 >::call( arg );
	}


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
	template<typename...Tuples>
	static void call(std::tuple<Tuples...> & arg)
	{
		Visitor< typename mp::get<0, TypeList>::type >::call( std::get<0>(arg) );
	}

	static void call()
	{
		Visitor< typename mp::get<0, TypeList>::type >::call();
	}
};

	
} // mp
} // psin

#endif // VISIT_HPP
