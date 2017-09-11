#ifndef NORMAL_FORCE_LINEAR_DASHPOT_FORCE_CPP
#define NORMAL_FORCE_LINEAR_DASHPOT_FORCE_CPP

#include <InteractionDefinitions/NormalForceLinearDashpotForce.hpp>

#include <string>

namespace psin {

template<> const std::string NamedType<NormalForceLinearDashpotForce>::name = "NormalForceLinearDashpotForce";

void Builder<NormalForceLinearDashpotForce>::setup(json&)
{}

} // psin


#endif // NORMAL_FORCE_LINEAR_DASHPOT_FORCE_CPP
