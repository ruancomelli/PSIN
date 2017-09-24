#ifndef CONTAINS_HPP
#define CONTAINS_HPP

#include <bool_constant.hpp>

namespace psin {
namespace mp {

template<typename TypeList, typename...ContainedTypes>
struct contains;

template<typename TypeList>
struct contains<TypeList> : std::true_type {};

template<typename TypeList, typename U, typename...Us>
struct contains<TypeList, U, Us...>
	: mp::bool_constant< contains<TypeList, U>::value and contains<TypeList, Us...>::value >
{};

template<typename U>
struct contains< mp::type_list<>, U> : std::false_type {};

template<typename T, typename...Ts, typename U>
struct contains< mp::type_list<T, Ts...>, U>
	: mp::bool_constant< std::is_same<T, U>::value or contains< mp::type_list<Ts...>, U>::value >
{};

} // mp
} // psin

#endif // CONTAINS_HPP
