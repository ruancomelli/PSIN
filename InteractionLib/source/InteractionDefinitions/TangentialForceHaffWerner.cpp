#ifndef TANGENTIAL_FORCE_HAFF_WERNER_CPP
#define TANGENTIAL_FORCE_HAFF_WERNER_CPP

#include <InteractionDefinitions/TangentialForceHaffWerner.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {

template<> const std::string NamedType<TangentialForceHaffWerner>::name = "TangentialForceHaffWerner";

template<>
void initializeInteraction<TangentialForceHaffWerner>(const json & j)
{}

template<>
void finalizeInteraction<TangentialForceHaffWerner>()
{}

} // psin


#endif // TANGENTIAL_FORCE_HAFF_WERNER_CPP
