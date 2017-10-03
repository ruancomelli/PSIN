#ifndef NORMAL_FORCE_HERTZ_CPP
#define NORMAL_FORCE_HERTZ_CPP

#include <InteractionDefinitions/NormalForceHertz.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {

template<> const std::string NamedType<NormalForceHertz>::name = "NormalForceHertz";

void Builder<NormalForceHertz>::setup(const json & j)
{}

} // psin


#endif // NORMAL_FORCE_HERTZ_CPP
