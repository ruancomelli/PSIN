#ifndef SIMULATION_TPP
#define SIMULATION_TPP

// JSONLib
#include <json.hpp>

// SimulationLib
#include <CommandLineParser.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <mp/visit.hpp>

// Standard
#include <fstream>

namespace psin {

template<typename>
struct Builder;

namespace detail {

template<typename I>
struct conditionally_build_interaction
{
	static void call(const string & interactionName, const path & filepath)
	{
		if( NamedType<I>::name == interactionName )
		{
			json j = read_json(filepath.string());

			Builder<I>::build(j.at(NamedType<I>::name));
		}
	}
};

template<typename EntityVector>
struct conditionally_build_entity
{
	using Entity = typename EntityVector::value_type;

	template<typename ParticleTuple>
	static void call(const string & entityType, const path & filepath, ParticleTuple & entities, string & entityName)
	{
		if( NamedType<Entity>::name == entityType)
		{
			json j = read_json(filepath.string());

			Entity entity = j;

			entityName = entity.getName();
			std::get<EntityVector>(entities).insert( entity );
		}
	}
};

} // detail

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulation<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
>::setup(int argc, char * argv[])
{
	fileTree["input"]["main"] = CommandLineParser::parseArgvIntoSimulationPath(argc, argv);

	json j = read_json(simulationPath);

	this->initialTime = j.at("initialTime");
	this->timeStep = j.at("timeStep");
	this->finalTime = j.at("finalTime");
	this->taylorOrder = j.at("taylorOrder");
	this->dimension = j.at("dimension");
	this->timeStepsForOutput = j.at("timeStepsForOutput");

	fileTree["output"]["main"] = path(j.at("mainOutputFolder"));
	filesystem::create_directories( fileTree["output"]["main"] );

	fileTree["output"]["particle"] = path(j.at("particleOutputFolder"));
	filesystem::create_directories( fileTree["output"]["particle"] );

	fileTree["output"]["boundary"] = path(j.at("boundaryOutputFolder"));
	filesystem::create_directories( fileTree["output"]["boundary"] );

	if(j.count("interactions") > 0)
	{
		json interactions = j["interactions"];
		for(json::iterator it = interactions.begin(); it != interactions.end(); ++it) 
		{
			string interactionName(it.key());
			path interactionInputFilePath(it.value());

			interactionsToUse.insert( interactionName );
			mp::visit<InteractionList, detail::conditionally_build_interaction>::call_same(interactionName, interactionInputFilePath);
			fileTree["input"]["interaction"][interactionName] = interactionInputFilePath;
		}
	}

	if(j.count("particles") > 0)
	{
		json particles = j["particles"];
		for(json::iterator it = particles.begin(); it != particles.end(); ++it) 
		{
			string particleType(it.key());
			string particleName;
			path particleInputFilePath(it.value());

			mp::visit<ParticleList, detail::conditionally_build_entity>::call_same(particleType, particleInputFilePath, particles, particleName);
			fileTree["input"]["particle"][particleName] = particleInputFilePath;
		}
	}
	
	if(j.count("boundaries") > 0)
	{
		json boundaries = j["boundaries"];
		for(json::iterator it = boundaries.begin(); it != boundaries.end(); ++it) 
		{
			string boundaryType(it.key());
			string boundaryName;
			path boundaryInputFilePath(it.value());

			mp::visit<BoundaryList, detail::conditionally_build_entity>::call_same(boundaryType, boundaryInputFilePath, boundaries, boundaryName);
			fileTree["input"]["boundary"][boundaryName] = boundaryInputFilePath;
		}
	}
	
}

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulation<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
>::outputMaindData()
{
	 
}


template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulation<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
>::simulate()
{
	
}


template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
template<typename I>
bool Simulation<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
>::useInteraction()
{
	return interactionsToUse.count(NamedType<I>::name) > 0;
}

} // psin

#endif // SIMULATION_TPP
