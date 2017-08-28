#ifndef NORMAL_FORCE_VISCOELASTIC_SPHERES_HPP
#define NORMAL_FORCE_VISCOELASTIC_SPHERES_HPP

// EntityLib
#include <SphericalParticle.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <MP/bool_type.hpp>

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates normal forces between two spherical particles according to equation (2.14) (see reference)
struct NormalForceViscoelasticSpheres
{
	using Radius = PropertyDefinitions::Radius;
	using ElasticModulus = PropertyDefinitions::ElasticModulus;
	using DissipativeConstant = PropertyDefinitions::DissipativeConstant;
	using PoissonRatio = PropertyDefinitions::PoissonRatio;

	template<typename P1, typename P2>
	struct check : bool_type<
		P1::template has_property<Radius>::value
		&& P1::template has_property<ElasticModulus>::value
		&& P1::template has_property<DissipativeConstant>::value
		&& P1::template has_property<PoissonRatio>::value
		&& is_spherical<P1>::value

		&& P2::template has_property<Radius>::value
		&& P2::template has_property<ElasticModulus>::value
		&& P2::template has_property<DissipativeConstant>::value
		&& P2::template has_property<PoissonRatio>::value
		&& is_spherical<P2>::value
		>
	{};

	template<typename...Ts, typename...Us>
	static Vector3D calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor);
};

template<> const std::string NamedType<NormalForceViscoelasticSpheres>::name = "NormalForceViscoelasticSpheres";

#include <InteractionDefinitions/NormalForceViscoelasticSpheres.tpp>

#endif
