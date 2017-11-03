#ifndef NORMAL_FORCE_HERTZ_TPP
#define NORMAL_FORCE_HERTZ_TPP

// EntityLib
#include <SphericalParticle.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// Standard
#include <algorithm>
#include <cmath>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates normal forces between two spherical particles according to equation (2.14) (see reference)
template<typename...Ts, typename...Us, typename Time>
Vector3D NormalForceHertz::calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, const Time &)
{
	// Calculations
	const double overlap = psin::overlap(particle, neighbor);
	
	if(overlap > 0)
	{
		// ---- Get physical properties and calculate effective parameters ----
		const double radius1 = particle.template get<Radius>();
		const double radius2 = neighbor.template get<Radius>();
		const double effectiveRadius = radius1 * radius2 / ( radius1 + radius2 );
		
		const double elasticModulus1 = particle.template get<ElasticModulus>();
		const double elasticModulus2 = neighbor.template get<ElasticModulus>();
		
		const double dissipativeConstant1 = particle.template get<DissipativeConstant>();
		const double dissipativeConstant2 = neighbor.template get<DissipativeConstant>();
		
		const double poissonRatio1 = particle.template get<PoissonRatio>();
		const double poissonRatio2 = neighbor.template get<PoissonRatio>();
		
		// ---- Calculate normal force ----
		const double overlapDerivative = psin::overlapDerivative(particle, neighbor);
		const double term1 = (4/3) * std::sqrt(effectiveRadius);
		const double term2 = std::sqrt(overlap) * (overlap + 0.5 * (dissipativeConstant1 + dissipativeConstant2) * overlapDerivative );
		const double term3 = (1 - poissonRatio1*poissonRatio1)/elasticModulus1 + (1 - poissonRatio2*poissonRatio2)/elasticModulus2;
		
		const double normalForceModulus = std::max( term1 * term2 / term3 , 0.0 );
		
		const Vector3D normalForce = - normalForceModulus * normalVersor(particle, neighbor);
		
		particle.addContactForce( normalForce );
		neighbor.addContactForce( - normalForce );

		return normalForce;
	}
	// else, no forces are added.
	return nullVector3D();
}

} // psin

#endif
