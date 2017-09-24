#ifndef LOGICAL_HPP
#define LOGICAL_HPP

#include <type_traits>

namespace psin {
namespace mp {

#ifdef __cpp_lib_logical_traits

using std::conjunction;
using std::disjunction;
using std::negation;

#else

template<class...> struct conjunction : std::true_type { };
template<class B1> struct conjunction<B1> : B1 { };
template<class B1, class... Bn>
struct conjunction<B1, Bn...> 
    : std::conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};


template<class...> struct disjunction : std::false_type { };
template<class B1> struct disjunction<B1> : B1 { };
template<class B1, class... Bn>
struct disjunction<B1, Bn...> 
    : std::conditional_t<bool(B1::value), B1, disjunction<Bn...>>  { };

template<class B>
struct negation : std::bool_constant<!bool(B::value)> { };

#endif

} // mp
} // psin

#endif // LOGICAL_HPP
