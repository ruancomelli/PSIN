#ifndef VARIANT_HPP
#define VARIANT_HPP

// boost
#include <boost/variant.hpp>

namespace psin {

namespace variant {
	using boost::variant;
	using boost::static_visitor;
	using boost::apply_visitor;
	using boost::get;
} // variant

} // psin

#endif //VARIANT_HPP
