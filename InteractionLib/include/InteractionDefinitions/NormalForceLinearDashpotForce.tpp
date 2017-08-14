#ifndef NORMAL_FORCE_LINEAR_DASHPOT_TPP
#define NORMAL_FORCE_LINEAR_DASHPOT_TPP

// EntityLib
#include <SphericalParticle.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// Standard
#include <algorithm>

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates normal forces between two spherical particles according to equation (2.8) (see reference)
template<typename...Ts, typename...Us>
Vector3D NormalForceLinearDashpotForce::calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor)
{
	const double overlap = ::overlap(particle, neighbor);
	
	if(overlap > 0)
	{
		// ---- Get physical properties and calculate effective parameters ----
		const double elasticModulus1 = particle.template get<ElasticModulus>();
		const double elasticModulus2 = neighbor.template get<ElasticModulus>();
		
		const double normalDissipativeConstant1 = particle.template get<NormalDissipativeConstant>();
		const double normalDissipativeConstant2 = neighbor.template get<NormalDissipativeConstant>();
		
		// ---- Calculate normal force ----
		const double overlapDerivative = ::overlapDerivative(particle, neighbor);
		
		const double normalForceModulus = std::max( (elasticModulus1 + elasticModulus2) * overlap + 
										(normalDissipativeConstant1 + normalDissipativeConstant2) * overlapDerivative , 0.0 );
		
		const Vector3D normalForce = - normalForceModulus * particle.normalVersor( neighbor );
		
		particle.addContactForce( normalForce );
		neighbor.addContactForce( - normalForce );
		return normalForce;
	}
	// else, no forces are added.
	return nullVector3D();
}

#endif