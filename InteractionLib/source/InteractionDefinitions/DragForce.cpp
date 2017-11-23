#ifndef DRAG_FORCE_CPP
#define DRAG_FORCE_CPP

#include <InteractionDefinitions/DragForce.hpp>

// JSONLib
#include <json.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {
	
template<> const string NamedType<DragForce>::name = "DragForce";

void Builder<DragForce>::setup(const json & j)
{}

} // psin

#endif // DRAG_FORCE_CPP
