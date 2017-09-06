#ifndef VISIT_HPP
#define VISIT_HPP

// UtilsLib
#include <mp/get.hpp>
#include <mp/length.hpp>

// Standard
#include <cstddef>
#include <tuple>

// There are three types of visit: call_same and call.
// call_same calls the Visitor's call function with the same argument. This can be void
// call calls the Visitor's call function using the i-th entry of the argument tuple.

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

	template<typename...Args>
	static void call_same(Args &...args)
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call(args...);
		visit< TypeList, Visitor, Pos-1 >::call_same(args...);
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

	template<typename...Args>
	static void call_same(Args &...args)
	{
		Visitor< typename mp::get<0, TypeList>::type >::call(args...);
	}
};

	
} // mp
} // psin

#endif // VISIT_HPP
