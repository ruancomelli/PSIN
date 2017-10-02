#ifndef GRAVITY_FORCE_HPP
#define GRAVITY_FORCE_HPP

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
		P1::template has_property<Mass>::value
		and std::is_same<P2, GravityField>::value
		>
	{};

	template<typename P1>
	static void calculate(P1 & particle, const GravityField & field);
};

template<>
struct Builder<GravityForce>
{
	static void setup(const json & j);
};

} // psin

#include <InteractionDefinitions/GravityForce.tpp>

#endif // GRAVITY_FORCE_HPP
