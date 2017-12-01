#ifndef DRAG_FORCE_CPP
#define DRAG_FORCE_CPP

#include <InteractionDefinitions/DragForce.hpp>

// JSONLib
#include <json.hpp>

// UtilsLib
#include <string.hpp>

namespace psin {
	
template<> const string NamedType<DragForce>::name = "DragForce";

template<>
void initializeInteraction<DragForce>(const json & j)
{}

template<>
void finalizeInteraction<DragForce>()
{}

} // psin

#endif // DRAG_FORCE_CPP
