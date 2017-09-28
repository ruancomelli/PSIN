#ifndef ANY_OF_HPP
#define ANY_OF_HPP

#include <mp/logical.hpp>

namespace psin {
namespace mp {

template<
	typename TypeList,
	template<typename> class Checker
>
struct any_of;

template<
	template<typename...> class TypeList,
	typename...Ts,
	template<typename> class Checker
>
struct any_of<
		TypeList<Ts...>,
		Checker>
	: mp::disjunction<
		Checker<Ts>...
	>
{};

} // mp
} // psin



#endif // ANY_OF_HPP
