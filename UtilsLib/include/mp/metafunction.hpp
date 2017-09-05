#ifndef METAFUNCTION_HPP
#define METAFUNCTION_HPP

namespace psin {
namespace mp {

template<typename T>
struct metafunction
{
	using type = T;
};

} // mp
} // psin

#endif // METAFUNCTION_HPP
