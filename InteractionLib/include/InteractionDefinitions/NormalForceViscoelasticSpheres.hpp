#ifndef NORMAL_FORCE_VISCOELASTIC_SPHERES_HPP
#define NORMAL_FORCE_VISCOELASTIC_SPHERES_HPP

// EntityLib
#include <SphericalParticle.hpp>

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates normal forces between two spherical particles according to equation (2.14) (see reference)
struct NormalForceViscoelasticSpheres
{
	template<typename...Ts, typename...Us>
	static Vector3D calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor);
};

#include <InteractionDefinitions/NormalForceViscoelasticSpheres.tpp>

#endif
