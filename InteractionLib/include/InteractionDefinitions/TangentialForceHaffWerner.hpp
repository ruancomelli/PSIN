#ifndef TANGENTIAL_FORCE_HAFF_WERNER_HPP
#define TANGENTIAL_FORCE_HAFF_WERNER_HPP

// EntityLib
#include <SphericalParticle.hpp>

// UtilsLib
#include <Builder.hpp>
#include <NamedType.hpp>
#include <mp/bool_constant.hpp>

// JSONLib
#include <json.hpp>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates tangential forces between two spherical particles according to equation (2.18) (see reference)
struct TangentialForceHaffWerner
{
	template<typename P1, typename P2>
	struct check : mp::bool_constant<
		has_property<P1, TangentialDamping>::value
		and has_property<P1, FrictionParameter>::value
		and is_spherical<P1>::value

		and has_property<P2, TangentialDamping>::value
		and has_property<P2, FrictionParameter>::value
		and is_spherical<P2>::value
		>
	{};
		
	template<typename...Ts, typename...Us, typename Time>
	static void calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, Time&&);
};

template<typename I>
void initializeInteraction(const json & j);

template<>
void initializeInteraction<TangentialForceHaffWerner>(const json & j);

template<typename I>
void finalizeInteraction();

template<>
void finalizeInteraction<TangentialForceHaffWerner>();

} // psin

#include <InteractionDefinitions/TangentialForceHaffWerner.tpp>

#endif
