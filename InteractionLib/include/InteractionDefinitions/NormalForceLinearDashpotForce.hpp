#ifndef NORMAL_FORCE_LINEAR_DASHPOT_HPP
#define NORMAL_FORCE_LINEAR_DASHPOT_HPP

// EntityLib
#include <SphericalParticle.hpp>

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

//		Calculates normal forces between two spherical particles according to equation (2.8) (see reference)
struct NormalForceLinearDashpotForce
{
	template<typename P1, typename P2>
	struct check : mp::disjunction<
		mp::conjunction<
			has_property<P1, ElasticModulus>,
			has_property<P1, NormalDissipativeConstant>,
			is_spherical<P1>,
			has_property<P2, ElasticModulus>,
			has_property<P2, NormalDissipativeConstant>,
			is_spherical<P2>
			>,
		mp::conjunction<
			has_property<P1, ElasticModulus>,
			has_property<P1, NormalDissipativeConstant>,
			is_spherical<P1>,
			has_property<P2, ElasticModulus>,
			has_property<P2, NormalDissipativeConstant>,
			is_plane<P2>
			>
		>
	{};

	template<typename P1, typename P2>
	constexpr static bool check_v = check<P1, P2>::value;

	template<typename...Ts, typename...Us, typename Time>
	static Vector3D calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, Time &&);

	template<typename...Ts, typename...Us, typename Time>
	static Vector3D calculate(SphericalParticle<Ts...> & particle, const FixedInfinitePlane<Us...> & neighbor, Time &&);
};

template<typename I>
void initializeInteraction(const json & j);

template<>
void initializeInteraction<NormalForceLinearDashpotForce>(const json & j);

template<typename I>
void finalizeInteraction();

template<>
void finalizeInteraction<NormalForceLinearDashpotForce>();

} // psin

#include <InteractionDefinitions/NormalForceLinearDashpotForce.tpp>

#endif