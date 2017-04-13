// What to do:
// Each property must be a class
// Each ForceModel must be a class

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
	LinearDashpotForce()
		: Named("LinearDashpotForce")
	{}

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

// ================================================================================================================================
// ================================================        INTERFACE 1       ======================================================
// ================================================================================================================================

Property<double> mass("Mass", setPositive);
Property<int> dimension("Dimension", setFromOneToThree);

class LinearDashpotForce : public NormalForceModel<SphericalParticle, SphericalParticle>
{
	LinearDashpotForce()
		: Named("LinearDashpotForce")
	{
		requireProperty(mass);
		requireProperty(moment_of_inertia);
		requireProperty(elastic_modulus);
		requireProperty(normal_dissipative_constant);
	}

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

class LinearDashpotForceWall : public NormalForceModel<SphericalParticle, FixedInfinitePlane>
{
	LinearDashpotForceWall()
		: Named("LinearDashpotForceWall")
	{
		// Require properties
	}

	Vector3D operator()( SphericalParticlePtr particle, FixedInfinitePlane neighbor )
	{
		const double overlap = particle->overlap(neighbor);
		
		if(overlap > 0)
		{
			// Calculations

			return normalForce;
		}
		// else, no forces are added.
		return nullVector3D();
	}
}

int main()
{
	Simulation<
		Properties<			
			Property<int>,
			Property<double>
		>,

		ForceModels<
			LinearDashpotForce,
			LinearDashpotForceWall
		>,

		Particles<
			SphericalParticle
		>,

		Boundaries<
			FixedInfinitePlane
		>
	> simulation;
	simulation.defaultSimulate("SimulationName", "RootPath");
}

// ================================================================================================================================
// ================================================        INTERFACE 2       ======================================================
// ================================================================================================================================

class Mass : public Property<double>
{
	Mass()
		: Named("Mass"),
		setter(setPositive)
	{
	}
}
class Dimension : public Property<int>
{
	Dimension()
		: Named("Dimension"),
		setter(setFromOneToThree)
	{
	}
}

class LinearDashpotForce :
	public NormalForceModel<
		SphericalParticle, 
		SphericalParticle, 
		Properties<
			Mass,
			MomentOfInertia,
			ElasticModulus,
			NormalDissipativeConstant
		>
	>
{
	LinearDashpotForce()
		: Named("LinearDashpotForce")
	{
	}

	Vector3D operator()( SphericalParticlePtr particle, SphericalParticlePtr neighbor )
	{
		const double overlap = particle->overlap(neighbor);
		
		if(overlap > 0)
		{
			// ---- Get physical properties and calculate effective parameters ----
			const double elasticModulus1 = particle->get<ElasticModulus>();
			// OR
			const double elasticModulus2 = get<ElasticModulus>(neighbor);
			
			const double normalDissipativeConstant1 = particle->get<NormalDissipativeConstant>();
			const double normalDissipativeConstant2 = neighbor->get<NormalDissipativeConstant>();
			
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

class LinearDashpotForceWall : public NormalForceModel<SphericalParticle, FixedInfinitePlane>
{
	// ...
}

int main()
{
	Simulation<
		ForceModels<
			LinearDashpotForce,
			LinearDashpotForceWall
		>,

		Particles<
			SphericalParticle
		>,

		Boundaries<
			FixedInfinitePlane
		>
	> simulation;
	simulation.defaultSimulate("SimulationName", "RootPath");
}