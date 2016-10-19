#ifndef UTILS_FOREACH_H
#define UTILS_FOREACH_H

#include <boost/foreach.hpp>

namespace utils{
    #define foreach BOOST_FOREACH
	#define reverse_foreach BOOST_REVERSE_FOREACH
} //namespace utils;

#endif //UTILS_SHARED_POINTER_H