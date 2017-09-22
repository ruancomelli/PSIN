#ifndef NORMAL_FORCE_LINEAR_DASHPOT_FORCE_CPP
#define NORMAL_FORCE_LINEAR_DASHPOT_FORCE_CPP

#include <InteractionDefinitions/NormalForceLinearDashpotForce.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {

template<> const std::string NamedType<NormalForceLinearDashpotForce>::name = "NormalForceLinearDashpotForce";

void Builder<NormalForceLinearDashpotForce>::setup(const json & j)
{}

} // psin


#endif // NORMAL_FORCE_LINEAR_DASHPOT_FORCE_CPP
