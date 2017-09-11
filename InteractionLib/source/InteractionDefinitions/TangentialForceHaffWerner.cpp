#ifndef TANGENTIAL_FORCE_HAFF_WERNER_CPP
#define TANGENTIAL_FORCE_HAFF_WERNER_CPP

#include <InteractionDefinitions/TangentialForceHaffWerner.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {

template<> const std::string NamedType<TangentialForceHaffWerner>::name = "TangentialForceHaffWerner";

void Builder<TangentialForceHaffWerner>::setup(json&)
{}

} // psin


#endif // TANGENTIAL_FORCE_HAFF_WERNER_CPP
