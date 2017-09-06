#ifndef TANGENTIAL_FORCE_HAFF_WERNER_HPP
#define TANGENTIAL_FORCE_HAFF_WERNER_HPP

// EntityLib
#include <SphericalParticle.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <mp/bool_constant.hpp>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates tangential forces between two spherical particles according to equation (2.18) (see reference)
struct TangentialForceHaffWerner
{
	using TangentialDamping = PropertyDefinitions::TangentialDamping;
	using FrictionParameter = PropertyDefinitions::FrictionParameter;

	template<typename P1, typename P2>
	struct check : mp::bool_constant<
		P1::template has_property<TangentialDamping>::value
		and P1::template has_property<FrictionParameter>::value
		and is_spherical<P1>::value

		and P2::template has_property<TangentialDamping>::value
		and P2::template has_property<FrictionParameter>::value
		and is_spherical<P2>::value
		>
	{};
		
	template<typename...Ts, typename...Us>
	static void calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, Vector3D normalForce, double timeStep);
};

} // psin

#include <InteractionDefinitions/TangentialForceHaffWerner.tpp>

#endif
