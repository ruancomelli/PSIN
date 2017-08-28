#ifndef STATIC_EXECUTE_HPP
#define STATIC_EXECUTE_HPP

// boost
#include <boost/preprocessor.hpp>

// This avoids repeating the BOOST_PP_CAT 5X
#define STATIC_EXECUTE \
  STATIC_EXECUTE_I(BOOST_PP_CAT(__StaticExecute__, __LINE__))

// This is the meat, a static instance of a class whose constructor runs your code
#define STATIC_EXECUTE_I(uniq_name)               \
static struct uniq_name {                         \
  uniq_name();                                    \
} BOOST_PP_CAT(uniq_name, __var);                 \
uniq_name::uniq_name()


#endif
