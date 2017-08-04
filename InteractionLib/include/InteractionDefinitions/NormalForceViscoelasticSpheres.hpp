#ifndef NORMAL_FORCE_VISCOELASTIC_SPHERES_HPP
#define NORMAL_FORCE_VISCOELASTIC_SPHERES_HPP

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

//		Calculates normal forces between two spherical particles according to equation (2.14) (see reference)
struct NormalForceViscoelasticSpheres
{
	template<typename...Ts, typename...Us>
	static Vector3D calculate(SphericalParticle<Ts...> particle1, SphericalParticle<Us...> particle2)
	{
		// Calculations
		const double overlap = particle->overlap(neighbor);
		
		if(overlap > 0)
		{
			// ---- Get physical properties and calculate effective parameters ----
			const double radius1 = particle->getGeometricParameter(RADIUS);
			const double radius2 = neighbor->getGeometricParameter(RADIUS);
			const double effectiveRadius = radius1 * radius2 / ( radius1 + radius2 );
			
			const double elasticModulus1 = particle->get( elastic_modulus );
			const double elasticModulus2 = neighbor->get( elastic_modulus );
			
			const double dissipativeConstant1 = particle->get( dissipative_constant );
			const double dissipativeConstant2 = neighbor->get( dissipative_constant );
			
			const double poissonRatio1 = particle->get( poisson_ratio );
			const double poissonRatio2 = neighbor->get( poisson_ratio );
			
			// ---- Calculate normal force ----
			const double overlapDerivative = particle->overlapDerivative( neighbor );
			const double term1 = (4/3) * sqrt(effectiveRadius);
			const double term2 = sqrt(overlap) * (overlap + 0.5 * (dissipativeConstant1 + dissipativeConstant2) * overlapDerivative );
			const double term3 = (1 - poissonRatio1*poissonRatio1)/elasticModulus1 + (1 - poissonRatio2*poissonRatio2)/elasticModulus2;
			
			const double normalForceModulus = max( term1 * term2 / term3 , 0.0 );
			
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
