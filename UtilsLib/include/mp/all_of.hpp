#ifndef ALL_OF_HPP
#define ALL_OF_HPP

#include <mp/logical.hpp>

namespace psin {
namespace mp {

template<
	typename TypeList,
	template<typename> class Checker
>
struct all_of;

template<
	template<typename...> class TypeList,
	typename...Ts,
	template<typename> class Checker
>
struct all_of<
		TypeList<Ts...>,
		Checker>
	: mp::conjunction<
		Checker<Ts>...
	>
{};

} // mp
} // psin

#endif // ALL_OF_HPP
