// ==============================================================================================================================
// ==============================================================================================================================
// Simulation.h
// ==============================================================================================================================

template<typename ... PropertyTypes>
struct Properties< PropertyTypes ... > {};

template<typename ... ForceModelTypes>
struct ForceModels< ForceModelTypes ... > {};

template<typename ... ParticleTypes>
struct Particles< ParticleTypes ... > {};

template<typename ... BoundaryTypes>
struct Boundaries< BoundaryTypes ... > {};

template<
	typename ... PropertyTypes,
	typename ... ForceModelTypes,
	typename ... ParticleTypes,
	typename ... BoundaryTypes
>
class Simulation<
	Properties< PropertyTypes... >,
	ForceModels< ForceModelTypes...>,
	Particles< ParticleTypes ... >,
	Boundaries< BoundaryTypes ... >
>
{


	private:
		std::map<
			std::string, 
			boost::variant< PropertyTypes... >
		> properties;

		std::map<
			std::string, 
			boost::variant< ForceModelTypes... >
		> forceModels;

		vector< boost::variant< ParticleTypes... > > particles;

		vector< boost::variant< BoundaryTypes... > > boundaries;
}

// Usage:
{
	Simulation<
		Properties<			
			Property<int, string>,
			Property<double>
		>,

		ForceModels<
			LinearDashpotForce
		>,

		Particles<
			SphericalParticle
		>,

		Boundaries<
			FixedInfinitePlane
		>
	> simulation;
}


// ==============================================================================================================================

// I don't know if we will do
Property<double> mass;
// Or
class Mass : public Property<double>;
// Or even
class Mass : public Property;

// ==============================================================================================================================

// ==============================================================================================================================
// ==============================================================================================================================
// ForceModel.h
// ==============================================================================================================================

class LinearDashpotForce : public NormalForceModel<SphericalParticle, SphericalParticle>
{
	Vector3D operator()( SphericalParticlePtr particle, SphericalParticlePtr neighbor )
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
}