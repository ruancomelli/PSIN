#ifndef GRAVITY_FORCE_HPP
#define GRAVITY_FORCE_HPP

// EntityLib
#include <PhysicalEntity.hpp>

// JSONLib
#include <json.hpp>

// EntityLib
#include <GravityField.hpp>

// UtilsLib
#include <Builder.hpp>
#include <metaprogramming.hpp>

// Standard
#include <type_traits>

namespace psin {

struct GravityForce
{
	template<typename P1, typename P2>
	struct check : mp::bool_constant<
		has_property<P1, Mass>::value
		and std::is_same<P2, GravityField>::value
		>
	{};

	template<typename P1, typename Time>
	static void calculate(P1 & particle, const GravityField & field, Time&&);
};

template<typename I>
void initializeInteraction(const json & j);

template<>
void initializeInteraction<GravityForce>(const json & j);

template<typename I>
void finalizeInteraction();

template<>
void finalizeInteraction<GravityForce>();

} // psin

#include <InteractionDefinitions/GravityForce.tpp>

#endif // GRAVITY_FORCE_HPP
