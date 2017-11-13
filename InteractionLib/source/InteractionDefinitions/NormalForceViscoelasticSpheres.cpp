#ifndef NORMAL_FORCE_HERTZ_CPP
#define NORMAL_FORCE_HERTZ_CPP

#include <InteractionDefinitions/NormalForceViscoelasticSpheres.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {

template<> const std::string NamedType<NormalForceViscoelasticSpheres>::name = "NormalForceViscoelasticSpheres";

void Builder<NormalForceViscoelasticSpheres>::setup(const json & j)
{}

} // psin


#endif // NORMAL_FORCE_HERTZ_CPP
