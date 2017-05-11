#ifndef UTILS_MAKE_UNIQUE_TYPE_LIST_HPP
#define UTILS_MAKE_UNIQUE_TYPE_LIST_HPP


#include <InsertNewTypesIntoTypeList.hpp>
#include <TypeList.hpp>

// ---- make_unique_type_list ----
template<typename ... Ts>
struct make_unique_type_list
{
	using value = typename insert_new_types_into_type_list<
		type_list<>,
		Ts...
	>::value;
};


#endif
