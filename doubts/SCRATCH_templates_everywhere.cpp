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
		>
	>
}


// ==============================================================================================================================
// I don't know if we will do
Property<double> mass;
// Or
class Mass : public Property<double>;
// Or even
class Mass : public Property
// ==============================================================================================================================



// ==============================================================================================================================
// ==============================================================================================================================
// ForceModel.h
// ==============================================================================================================================

