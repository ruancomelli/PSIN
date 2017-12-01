#ifndef ELECTROSTATIC_FORCE_CPP
#define ELECTROSTATIC_FORCE_CPP

#include <InteractionDefinitions/ElectrostaticForce.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {
	
template<> const string NamedType<ElectrostaticForce>::name = "ElectrostaticForce";

template<>
void initializeInteraction<ElectrostaticForce>(const json & j)
{}

template<>
void finalizeInteraction<ElectrostaticForce>()
{}

} // psin


#endif // ELECTROSTATIC_FORCE_CPP
