#ifndef NORMAL_FORCE_LINEAR_DASHPOT_HPP
#define NORMAL_FORCE_LINEAR_DASHPOT_HPP

// EntityLib
#include <SphericalParticle.hpp>

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates normal forces between two spherical particles according to equation (2.8) (see reference)
struct NormalForceLinearDashpotForce
{
	using ElasticModulus = PropertyDefinitions::ElasticModulus;
	using NormalDissipativeConstant = PropertyDefinitions::NormalDissipativeConstant;

	template<typename P>
	constexpr static bool check = P::template has_property<ElasticModulus>
		&& P::template has_property<NormalDissipativeConstant>
		&& is_spherical<P>::value;

	template<typename...Ts, typename...Us>
	static Vector3D calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor);
};

#include <InteractionDefinitions/NormalForceLinearDashpotForce.tpp>

#endif