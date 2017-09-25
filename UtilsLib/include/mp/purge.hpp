#ifndef PURGE_HPP
#define PURGE_HPP

#include <mp/purge.tpp>

namespace psin {
namespace mp {

template<typename TypeList, template<typename> class CheckMF>
struct purge
	: detail::purge_apply<TypeList, CheckMF>
{};
	
} // mp
} // psin

#endif // PURGE_HPP
