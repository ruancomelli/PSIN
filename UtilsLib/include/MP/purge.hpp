#ifndef PURGE_HPP
#define PURGE_HPP

#include <MP/purge.tpp>

namespace mp {
	struct purge
	{
		template<typename TypeList, template<typename> class CheckMF>
		struct apply : traits::purge_apply<TypeList, CheckMF>
		{};
	};
} // mp

#endif // PURGE_HPP
