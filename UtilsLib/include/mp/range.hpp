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
namespace detail {

template<typename T, T Begin, T Step, T End, typename Enable = void>
struct integer_range_impl;

template<typename T, T Begin, T Step, T End>
struct integer_range_impl<T, Begin, Step, End, typename std::enable_if<(Begin < End)>::type>
	: mp::metafunction<
		typename mp::concatenate<
			mp::integer_sequence<T, Begin>,
			typename integer_range_impl<T, Begin+Step, Step, End>::type
		>::type
	>
{};

template<typename T, T Begin, T Step, T End>
struct integer_range_impl<T, Begin, Step, End, typename std::enable_if<not(Begin < End)>::type>
	: mp::metafunction<
		mp::integer_sequence<T>
	>
{};

} // detail

template<typename T, T...ts>
struct integer_range;

template<typename T, T Begin, T Step, T End>
struct integer_range<T, Begin, Step, End>
	: detail::integer_range_impl<T, Begin, Step, End>
{};

template<typename T, T Begin, T End>
struct integer_range<T, Begin, End>
	: detail::integer_range_impl<T, Begin, T(1), End>
{};

template<typename T, T End>
struct integer_range<T, End>
	: detail::integer_range_impl<T, T(0), T(1), End>
{};

template<std::size_t ... ts>
using range = integer_range<std::size_t, ts...>;

} // mp
} // psin

#endif // RANGE_HPP
