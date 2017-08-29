#ifndef TANGENTIAL_FORCE_CUNDALL_STRACK_TPP
#define TANGENTIAL_FORCE_CUNDALL_STRACK_TPP

// EntityLib
#include <SphericalParticle.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// Standard
#include <algorithm>
#include <map>
#include <utility>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates tangential forces between two spherical particles according to equation (2.21) (see reference)
template<typename...Ts, typename...Us>
void TangentialForceCundallStrack::calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, Vector3D normalForce, double timeStep)
{
	if( touch(particle, neighbor) )
	{
		if( !checkCollision(particle, neighbor) )
		{
			startCollision( particle, neighbor );
			setZeta( particle, neighbor, nullVector3D() );
		}
		// ---- Getting particles properties and parameters ----
		const Vector3D position1 = particle.getPosition();
		const Vector3D position2 = neighbor.getPosition();
		const double tangentialKappa1 = particle.template get<TangentialKappa>();
		const double tangentialKappa2 = neighbor.template get<TangentialKappa>();
		const double effectiveTangentialKappa = std::min( tangentialKappa1 , tangentialKappa2 );
			
		const double frictionParameter1 = particle.template get<FrictionParameter>();
		const double frictionParameter2 = neighbor.template get<FrictionParameter>();
		const double effectiveFrictionParameter = std::min( frictionParameter1, frictionParameter2 );
		
		// Calculate tangential force
		const Vector3D contactPoint = psin::contactPoint(particle, neighbor);
		
		const Vector3D relativeTangentialVelocity = particle.relativeTangentialVelocity( neighbor );
		
		const Vector3D tangentialVersor = particle.tangentialVersor( neighbor );
		addZeta( particle, neighbor, relativeTangentialVelocity * timeStep );
		
		const int index1 = std::min( particle.getHandle(), neighbor.getHandle() );
		const int index2 = std::max( particle.getHandle(), neighbor.getHandle() ) - index1 - 1;
		const Vector3D tangentialForce = std::min( effectiveTangentialKappa * cummulativeZeta[ std::pair<unsigned, unsigned>(index1, index2) ].length() , 
			effectiveFrictionParameter * normalForce.length() ) * tangentialVersor;
		
		particle.addContactForce( tangentialForce );
		neighbor.addContactForce( - tangentialForce );
									
		particle.addTorque( cross(contactPoint - position1, tangentialForce) );
		neighbor.addTorque( cross(contactPoint - position2, - tangentialForce) );
	}// else, no forces and no torques are added.
	else if( checkCollision(particle, neighbor) )
	{
		endCollision(particle, neighbor);
	}
}

} // psin

#endif
