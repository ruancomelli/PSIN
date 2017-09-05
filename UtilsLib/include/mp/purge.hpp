#ifndef PURGE_HPP
#define PURGE_HPP

#include <mp/purge.tpp>

namespace psin {
namespace mp {
	struct purge
	{
		template<typename TypeList, template<typename> class CheckMF>
		struct apply : detail::purge_apply<TypeList, CheckMF>
		{};
	};
} // mp
} // psin

#endif // PURGE_HPP
