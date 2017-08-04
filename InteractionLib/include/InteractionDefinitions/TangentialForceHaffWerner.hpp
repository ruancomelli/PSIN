#ifndef TANGENTIAL_FORCE_HAFF_WERNER_HPP
#define TANGENTIAL_FORCE_HAFF_WERNER_HPP

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates tangential forces between two spherical particles according to equation (2.18) (see reference)
struct TangentialForceHaffWerner
{
	template<typename...Ts, typename...Us>
	static void calculate(SphericalParticle<Ts...> particle1, SphericalParticle<Us...> particle2, Vector3D normalForce, double timeStep)
	{
		if( particle->touches(neighbor) )
		{
			// ---- Getting particles properties and parameters ----
			const double radius1 = particle->getGeometricParameter(RADIUS);
			const double radius2 = neighbor->getGeometricParameter(RADIUS);
			const Vector3D position1 = particle->getPosition(0);
			const Vector3D position2 = neighbor->getPosition(0);
			const double tangentialDamping1 = particle->get( tangential_damping );
			const double tangentialDamping2 = neighbor->get( tangential_damping );
			const double effectiveTangentialDamping = min( tangentialDamping1 , tangentialDamping2 );
				
			const double frictionParameter1 = particle->get( friction_parameter );
			const double frictionParameter2 = neighbor->get( friction_parameter );
			const double effectiveFrictionParameter = min( frictionParameter1, frictionParameter2 );
			
			// ---- Calculate tangential force ----
			const Vector3D contactPoint = particle->contactPoint( neighbor );		
			const Vector3D relativeTangentialVelocity = particle->relativeTangentialVelocity( neighbor ) ;
			
			const Vector3D tangentialVersor = particle->tangentialVersor( neighbor );
			const Vector3D tangentialForce =	min( effectiveTangentialDamping * relativeTangentialVelocity.length() , 
				effectiveFrictionParameter * normalForce.length() ) * tangentialVersor;
			
			particle->addContactForce( tangentialForce );
			neighbor->addContactForce( - tangentialForce );
										
			particle->addTorque( cross(contactPoint - position1, tangentialForce) );
			neighbor->addTorque( cross(contactPoint - position2, - tangentialForce) );
		}
		// else, no forces and no torques are added.
	}
};

#endif
