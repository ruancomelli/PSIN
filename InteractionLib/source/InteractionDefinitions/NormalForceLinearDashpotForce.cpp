#ifndef NORMAL_FORCE_LINEAR_DASHPOT_FORCE_CPP
#define NORMAL_FORCE_LINEAR_DASHPOT_FORCE_CPP

#include <InteractionDefinitions/NormalForceLinearDashpotForce.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {

template<> const std::string NamedType<NormalForceLinearDashpotForce>::name = "NormalForceLinearDashpotForce";

template<>
void initializeInteraction<NormalForceLinearDashpotForce>(const json & j)
{}

template<>
void finalizeInteraction<NormalForceLinearDashpotForce>()
{}

} // psin


#endif // NORMAL_FORCE_LINEAR_DASHPOT_FORCE_CPP
