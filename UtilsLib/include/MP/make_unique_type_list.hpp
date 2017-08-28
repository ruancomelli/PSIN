#ifndef MAKE_UNIQUE_TYPE_LIST_HPP
#define MAKE_UNIQUE_TYPE_LIST_HPP

#include <mp/type_list.hpp>

// ---- make_unique_type_list ----
namespace psin {
namespace mp {

template<typename ... Ts>
using make_unique_type_list = typename type_list<>::append_if_new_types<Ts...>;

} // mp
} // psin

#endif
