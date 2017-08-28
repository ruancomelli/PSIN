#ifndef TYPE_COLLECTION_TPP
#define TYPE_COLLECTION_TPP

// UtilsLib
#include <mp/type_list.hpp>

// Standard
#include <type_traits>

namespace psin {
	
namespace mp {
	template<typename...Ts>
	struct type_collection;
} // mp

namespace detail
{
	template<typename T, typename U>
	struct is_superset_of;

	template<typename...Ts>
	struct is_superset_of< mp::type_collection<Ts...>,  mp::type_collection<> >
		: std::true_type
	{};

	template<typename...Ts, typename U, typename...Us>
	struct is_superset_of< mp::type_collection<Ts...>,  mp::type_collection<U, Us...> >
		: std::conditional<
			mp::type_list<Ts...>::template contains<U, Us...>,
			std::true_type,
			std::false_type
		>::type
	{};

	template<typename T, typename U>
	using is_subset_of = is_superset_of<U, T>;
} // detail

} // psin

#endif