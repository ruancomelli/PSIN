#ifndef RANGE_HPP
#define RANGE_HPP

// UtilsLib
#include <mp/concatenate.hpp>
#include <mp/integer_sequence.hpp>
#include <mp/metafunction.hpp>

// Standard
#include <utility>

namespace psin {
namespace mp {

template<typename T, T...ts, typename=void>
struct integer_range;

template<typename T, T Begin, T Step, T End>
struct integer_range<T, Begin, Step, End, typename std::enable_if<(Begin < End), void>::type>
	: mp::metafunction<
		typename mp::concatenate<
			mp::integer_sequence<T, Begin>,
			typename integer_range<T, Begin+Step, End>::type
		>::type
	>
{};

template<typename T, T Begin, T Step, T End>
struct integer_range<T, Begin, Step, End, typename std::enable_if<not(Begin < End), void>::type>
	: mp::metafunction<
		mp::integer_sequence<T>
	>
{};

template<typename T, T Begin, T End>
struct integer_range<T, Begin, End>
	: mp::metafunction<
		integer_range<T, Begin, T(1), End>::type
	>
{};

template<typename T, T End>
struct integer_range<T, End>
	: mp::metafunction<
		integer_range<T, T(0), End>::type
	>
{};

template<std::size_t ... ts>
using range = integer_range<std::size_t, ts...>;

} // mp
} // psin

#endif // RANGE_HPP
