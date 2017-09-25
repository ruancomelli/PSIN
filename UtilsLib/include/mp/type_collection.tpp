#ifndef TYPE_COLLECTION_TPP
#define TYPE_COLLECTION_TPP

// UtilsLib
#include <mp/bool_constant.hpp>
#include <mp/contains.hpp>

// Standard
#include <type_traits>

namespace psin {
namespace mp {
namespace detail
{

template<typename Pack1, typename Pack2>
struct is_superset_of;

template<typename Pack1, template<typename...> class Pack2, typename...Us>
struct is_superset_of< Pack1,  Pack2<Us...> >
	: mp::bool_constant<
		mp::contains<
			Pack1,
			Us...
		>::value
	>
{};

template<typename T, typename U>
using is_subset_of = is_superset_of<U, T>;

} // detail
} // mp
} // psin

#endif