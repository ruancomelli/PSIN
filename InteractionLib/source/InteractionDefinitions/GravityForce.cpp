#ifndef GRAVITY_FORCE_CPP
#define GRAVITY_FORCE_CPP

#include <InteractionDefinitions/GravityForce.hpp>

// JSONLib
#include <json.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {
	
template<> const string NamedType<GravityForce>::name = "GravityForce";

template<>
void initializeInteraction<GravityForce>(const json & j)
{}

template<>
void finalizeInteraction<GravityForce>()
{}

} // psin

#endif // GRAVITY_FORCE_CPP
