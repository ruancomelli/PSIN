#ifndef ELECTROSTATIC_FORCE_CPP
#define ELECTROSTATIC_FORCE_CPP

#include <InteractionDefinitions/ElectrostaticForce.hpp>

#include <string>

namespace psin {
	
template<> const std::string NamedType<ElectrostaticForce>::name = "ElectrostaticForce";

} // psin


#endif // ELECTROSTATIC_FORCE_CPP
