#ifndef NORMAL_FORCE_LINEAR_DASHPOT_HPP
#define NORMAL_FORCE_LINEAR_DASHPOT_HPP

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates normal forces between two spherical particles according to equation (2.8) (see reference)
struct NormalForceLinearDashpotForce
{
	template<typename...Ts, typename...Us>
	static Vector3D calculate(SphericalParticle<Ts...> particle1, SphericalParticle<Us...> particle2)
	{
		const double overlap = particle->overlap(neighbor);
		
		if(overlap > 0)
		{
			// ---- Get physical properties and calculate effective parameters ----
			const double elasticModulus1 = particle->get( elastic_modulus );
			const double elasticModulus2 = neighbor->get( elastic_modulus );
			
			const double normalDissipativeConstant1 = particle->get( normal_dissipative_constant );
			const double normalDissipativeConstant2 = neighbor->get( normal_dissipative_constant );
			
			// ---- Calculate normal force ----
			const double overlapDerivative = particle->overlapDerivative( neighbor );
			
			const double normalForceModulus = max( (elasticModulus1 + elasticModulus2) * overlap + 
											(normalDissipativeConstant1 + normalDissipativeConstant2) * overlapDerivative , 0.0 );
			
			const Vector3D normalForce = - normalForceModulus * particle->normalDirection( neighbor );
			
			particle->addContactForce( normalForce );
			neighbor->addContactForce( - normalForce );
			return normalForce;
		}
		// else, no forces are added.
		return nullVector3D();
	}
};

#endif