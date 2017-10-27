#ifndef NORMAL_FORCE_LINEAR_DASHPOT_HPP
#define NORMAL_FORCE_LINEAR_DASHPOT_HPP

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

//		Calculates normal forces between two spherical particles according to equation (2.8) (see reference)
struct NormalForceLinearDashpotForce
{
	template<typename P1, typename P2>
	struct check : mp::bool_constant<
		has_property<P1, ElasticModulus>::value
		and has_property<P1, NormalDissipativeConstant>::value
		and is_spherical<P1>::value
		and has_property<P2, ElasticModulus>::value
		and has_property<P2, NormalDissipativeConstant>::value
		and is_spherical<P2>::value
		>
	{};

	template<typename P1, typename P2>
	constexpr static bool check_v = check<P1, P2>::value;

	template<typename...Ts, typename...Us, typename Time>
	static Vector3D calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, const Time &);
};

template<>
struct Builder<NormalForceLinearDashpotForce>
{
	static void setup(const json & j);
};

} // psin

#include <InteractionDefinitions/NormalForceLinearDashpotForce.tpp>

#endif