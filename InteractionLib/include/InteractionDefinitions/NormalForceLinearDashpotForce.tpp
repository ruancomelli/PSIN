#ifndef NORMAL_FORCE_LINEAR_DASHPOT_TPP
#define NORMAL_FORCE_LINEAR_DASHPOT_TPP

// EntityLib
#include <SphericalParticle.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// Standard
#include <algorithm>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates normal forces between two spherical particles according to equation (2.8) (see reference)
template<typename...Ts, typename...Us, typename Time>
Vector3D NormalForceLinearDashpotForce::calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, Time&&)
{
	std::cout << "Calculating NormalForceLinearDashpotForce" << std::endl; // DEBUG

	const double overlap = psin::overlap(particle, neighbor);
	
	if(overlap > 0)
	{
		std::cout << "Positive overlap" << std::endl; // DEBUG

		// ---- Get physical properties and calculate effective parameters ----
		const double elasticModulus1 = particle.template get<ElasticModulus>();
		const double elasticModulus2 = neighbor.template get<ElasticModulus>();
		
		const double normalDissipativeConstant1 = particle.template get<NormalDissipativeConstant>();
		const double normalDissipativeConstant2 = neighbor.template get<NormalDissipativeConstant>();
		
		// ---- Calculate normal force ----
		const double overlapDerivative = psin::overlapDerivative(particle, neighbor);
		
		const double normalForceModulus = std::max( (elasticModulus1 + elasticModulus2) * overlap + 
										(normalDissipativeConstant1 + normalDissipativeConstant2) * overlapDerivative , 0.0 );
		
		const Vector3D normalForce = - normalForceModulus * normalVersor(particle, neighbor);
		

		particle.addContactForce( normalForce );
		neighbor.addContactForce( - normalForce );

		std::cout << "Setting normal force" << std::endl; // DEBUG
		particle.setNormalForce(neighbor, normalForce);
		std::cout << "Normal force between " << particle.getName() << " and " << neighbor.getName() << ": " << particle.getNormalForce(neighbor) << std::endl; // DEBUG

		neighbor.setNormalForce(particle, - normalForce);

		return normalForce;
	}
	// else, no forces are added.
	return nullVector3D();
}

template<typename...Ts, typename...Us, typename Time>
Vector3D NormalForceLinearDashpotForce::calculate(SphericalParticle<Ts...> & particle, const FixedInfinitePlane<Us...> & neighbor, Time&&)
{
	const double overlap = psin::overlap(particle, neighbor);
	
	if(overlap > 0)
	{
		// ---- Get physical properties and calculate effective parameters ----
		const double elasticModulus1 = particle.template get<ElasticModulus>();
		const double elasticModulus2 = neighbor.template get<ElasticModulus>();
		
		const double normalDissipativeConstant1 = particle.template get<NormalDissipativeConstant>();
		const double normalDissipativeConstant2 = neighbor.template get<NormalDissipativeConstant>();
		
		// ---- Calculate normal force ----
		const double overlapDerivative = psin::overlapDerivative(particle, neighbor);
		
		const double normalForceModulus = std::max( (elasticModulus1 + elasticModulus2) * overlap + 
										(normalDissipativeConstant1 + normalDissipativeConstant2) * overlapDerivative , 0.0 );
		
		const Vector3D normalForce = - normalForceModulus * normalVersor(particle, neighbor);
		
		particle.addContactForce( normalForce );

		particle.setNormalForce(neighbor, normalForce);
		
		return normalForce;
	}
	// else, no forces are added.
	return nullVector3D();
}

} // psin

#endif