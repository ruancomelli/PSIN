#ifndef NORMAL_FORCE_HERTZ_CPP
#define NORMAL_FORCE_HERTZ_CPP

#include <InteractionDefinitions/NormalForceViscoelasticSpheres.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {

template<> const std::string NamedType<NormalForceViscoelasticSpheres>::name = "NormalForceViscoelasticSpheres";

template<>
void initializeInteraction<NormalForceViscoelasticSpheres>(const json & j)
{}

template<>
void finalizeInteraction<NormalForceViscoelasticSpheres>()
{}

} // psin


#endif // NORMAL_FORCE_HERTZ_CPP
