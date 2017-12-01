#ifndef DRAG_FORCE_HPP
#define DRAG_FORCE_HPP

// EntityLib
#include <SphericalParticle.hpp>
#include <SurroundingFluid.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// UtilsLib
#include <Builder.hpp>
#include <NamedType.hpp>
#include <mp/logical.hpp>

// JSONLib
#include <json.hpp>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle
struct DragForce
{
	template<typename Particle, typename Fluid>
	struct check : mp::conjunction<
			is_spherical<Particle>,
			is_surrounding_fluid<Fluid>,
			has_property<Fluid, SpecificMass>
		>
	{};

	template<typename Particle, typename Fluid>
	constexpr static bool check_v = check<Particle, Fluid>::value;

	template<typename Particle, typename Fluid, typename T>
	static void calculate(Particle & particle, const Fluid & neighbor, T&&);

	template<typename Particle, typename Fluid>
	static double dragCoefficient(Particle & particle, const Fluid & neighbor);
};

template<typename I>
void initializeInteraction(const json & j);

template<>
void initializeInteraction<DragForce>(const json & j);

template<typename I>
void finalizeInteraction();

template<>
void finalizeInteraction<DragForce>();

} // psin

#include <InteractionDefinitions/DragForce.tpp>

#endif
