#ifndef NONE_OF_HPP
#define NONE_OF_HPP

#include <mp/any_of.hpp>
#include <mp/logical.hpp>

namespace psin {
namespace mp {

template<
	typename TypeList,
	template<typename> class Checker
>
struct none_of
	: mp::negation<
		mp::any_of<
			TypeList,
			Checker
		>
	>
{};

} // mp
} // psin

#endif // NONE_OF_HPP
