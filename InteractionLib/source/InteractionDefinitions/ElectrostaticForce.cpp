#ifndef ELECTROSTATIC_FORCE_CPP
#define ELECTROSTATIC_FORCE_CPP

#include <InteractionDefinitions/ElectrostaticForce.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {
	
template<> const std::string NamedType<ElectrostaticForce>::name = "ElectrostaticForce";

void Builder<ElectrostaticForce>::setup(json&)
{}

} // psin


#endif // ELECTROSTATIC_FORCE_CPP
