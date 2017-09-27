#ifndef VISIT_HPP
#define VISIT_HPP

// UtilsLib
#include <mp/get.hpp>
#include <mp/length.hpp>

// Standard
#include <cstddef>
#include <type_traits>
#include <tuple>

// There are two types of visit: call_same and call.
// call_same calls the Visitor's call function with the same argument. This can be void
// call calls the Visitor's call function using the i-th entry of the argument tuple.

namespace psin {
namespace mp {

#if __cplusplus >= 201703L

template<
	typename TypeList,
	template<typename> class Visitor,
	std::size_t RevertedPosition = mp::length<TypeList>::value - 1
>
struct visit;

template<
	template<typename...> typename TL,
	typename...Ts,
	template<typename> typename Visitor,
	std::size_t RevertedPosition
>
struct visit<TL<Ts...>, Visitor, RevertedPosition>
{
	using TypeList = TL<Ts...>;

	constexpr static std::size_t Pos = mp::length<TypeList>::value - 1 - RevertedPosition;

	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call(Tuple & arg )
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call( std::get<Pos>(arg) );
		visit< TypeList, Visitor, RevertedPosition-1 >::call( arg );
	}

	template<typename...Args>
	static void call_same(Args &...args)
	{
		(Visitor<Ts>::call(args...), ...);
	}


	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call(Tuple & arg )
	{}
};

template<
	template<typename...> typename TL,
	typename...Ts,
	template<typename> typename Visitor
>
struct visit<TL<Ts...>, Visitor, 0>
{
	using TypeList = TL<Ts...>;

	constexpr static std::size_t Pos = mp::length<TypeList>::value - 1;

	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call(Tuple & arg)
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call( std::get<Pos>(arg) );
	}

	template<typename...Args, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call_same(Args &...args)
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call(args...);
	}


	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call(Tuple & arg )
	{}

	template<typename...Args, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call_same(Args &...args)
	{}
};

#else

template<
	typename TypeList,
	template<typename> class Visitor,
	std::size_t RevertedPosition = mp::length<TypeList>::value - 1
>
struct visit
{
	constexpr static std::size_t Pos = mp::length<TypeList>::value - 1 - RevertedPosition;

	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call(Tuple & arg )
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call( std::get<Pos>(arg) );
		visit< TypeList, Visitor, RevertedPosition-1 >::call( arg );
	}

	template<typename...Args, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call_same(Args &...args)
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call(args...);
		visit< TypeList, Visitor, RevertedPosition-1 >::call_same(args...);
	}


	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call(Tuple & arg )
	{}

	template<typename...Args, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call_same(Args &...args)
	{}
};

template<
	typename TypeList,
	template<typename> class Visitor
>
struct visit<TypeList, Visitor, 0>
{
	constexpr static std::size_t Pos = mp::length<TypeList>::value - 1;

	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call(Tuple & arg)
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call( std::get<Pos>(arg) );
	}

	template<typename...Args, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength > 0)>::type call_same(Args &...args)
	{
		Visitor< typename mp::get<Pos, TypeList>::type >::call(args...);
	}


	template<typename Tuple, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call(Tuple & arg )
	{}

	template<typename...Args, std::size_t TypeListLength = mp::length<TypeList>::value>
	static typename std::enable_if<(TypeListLength == 0)>::type call_same(Args &...args)
	{}
};

#endif

	
} // mp
} // psin

#endif // VISIT_HPP
