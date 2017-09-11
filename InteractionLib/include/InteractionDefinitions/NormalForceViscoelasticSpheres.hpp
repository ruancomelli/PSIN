#ifndef NORMAL_FORCE_VISCOELASTIC_SPHERES_HPP
#define NORMAL_FORCE_VISCOELASTIC_SPHERES_HPP

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

//		Calculates normal forces between two spherical particles according to equation (2.14) (see reference)
struct NormalForceViscoelasticSpheres
{
	
	
	
	

	template<typename P1, typename P2>
	struct check : mp::bool_constant<
		P1::template has_property<Radius>::value
		and P1::template has_property<ElasticModulus>::value
		and P1::template has_property<DissipativeConstant>::value
		and P1::template has_property<PoissonRatio>::value
		and is_spherical<P1>::value

		and P2::template has_property<Radius>::value
		and P2::template has_property<ElasticModulus>::value
		and P2::template has_property<DissipativeConstant>::value
		and P2::template has_property<PoissonRatio>::value
		and is_spherical<P2>::value
		>
	{};

	template<typename...Ts, typename...Us>
	static Vector3D calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor);
};

} // psin

#include <InteractionDefinitions/NormalForceViscoelasticSpheres.tpp>

#endif
