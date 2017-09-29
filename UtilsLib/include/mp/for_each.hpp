#ifndef FOR_EACH_HPP
#define FOR_EACH_HPP

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>

namespace psin {
namespace mp {

using boost::mpl::for_each;
using boost::mpl::range_c;

template<typename T>
struct provide_indices
	: range_c<std::size_t, 0, length<T>::value>
{};

} // mp
} // psin

#endif // FOR_EACH_HPP
