#ifndef TANGENTIAL_FORCE_HAFF_WERNER_TPP
#define TANGENTIAL_FORCE_HAFF_WERNER_TPP

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

//		Calculates tangential forces between two spherical particles according to equation (2.18) (see reference)
template<typename...Ts, typename...Us>
void TangentialForceHaffWerner::calculate(SphericalParticle<Ts...> & particle, SphericalParticle<Us...> & neighbor, Vector3D normalForce, double timeStep)
{
	using TangentialDamping = PropertyDefinitions::TangentialDamping;
	using FrictionParameter = PropertyDefinitions::FrictionParameter;

	if( touch(particle, neighbor) )
	{
		// ---- Getting particles properties and parameters ----
		const Vector3D position1 = particle.getPosition();
		const Vector3D position2 = neighbor.getPosition();
		const double tangentialDamping1 = particle.template get<TangentialDamping>();
		const double tangentialDamping2 = neighbor.template get<TangentialDamping>();
		const double effectiveTangentialDamping = std::min( tangentialDamping1 , tangentialDamping2 );
			
		const double frictionParameter1 = particle.template get<FrictionParameter>();
		const double frictionParameter2 = neighbor.template get<FrictionParameter>();
		const double effectiveFrictionParameter = std::min( frictionParameter1, frictionParameter2 );
		
		// ---- Calculate tangential force ----
		const Vector3D contactPoint = ::contactPoint(particle, neighbor);		
		const Vector3D relativeTangentialVelocity = particle.relativeTangentialVelocity(neighbor) ;
		
		const Vector3D tangentialVersor = particle.tangentialVersor( neighbor );
		const Vector3D tangentialForce =	std::min( effectiveTangentialDamping * relativeTangentialVelocity.length() , 
			effectiveFrictionParameter * normalForce.length() ) * tangentialVersor;
		
		particle.addContactForce( tangentialForce );
		neighbor.addContactForce( - tangentialForce );
									
		particle.addTorque( cross(contactPoint - position1, tangentialForce) );
		neighbor.addTorque( cross(contactPoint - position2, - tangentialForce) );
	}
	// else, no forces and no torques are added.
}

#endif
