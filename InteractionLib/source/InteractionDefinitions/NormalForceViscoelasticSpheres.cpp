#ifndef NORMAL_FORCE_VISCOELASTIC_SPHERES_CPP
#define NORMAL_FORCE_VISCOELASTIC_SPHERES_CPP

#include <InteractionDefinitions/NormalForceViscoelasticSpheres.hpp>

#include <string>

namespace psin {

template<> const std::string NamedType<NormalForceViscoelasticSpheres>::name = "NormalForceViscoelasticSpheres";

void Builder<NormalForceViscoelasticSpheres>::setup(json&)
{}

} // psin


#endif // NORMAL_FORCE_VISCOELASTIC_SPHERES_CPP
