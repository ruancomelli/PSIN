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
	fileTree["output"]["particle"] = path(j.at("particleOutputFolder"));
	fileTree["output"]["boundary"] = path(j.at("boundaryOutputFolder"));

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
>::outputMainData()
{
	filesystem::create_directories( fileTree["output"]["main"] );
	filesystem::create_directories( fileTree["output"]["main"] / path("particle"));
	filesystem::create_directories( fileTree["output"]["main"] / path("boundary"));
	filesystem::create_directories( fileTree["output"]["main"] / path("interaction"));
	filesystem::create_directories( fileTree["output"]["particle"] );
	filesystem::create_directories( fileTree["output"]["boundary"] );

	json mainOutput{
		{"initialTime", this->initialTime},
		{"timeStep", this->timeStep},
		{"finalTime", this->finalTime},
		{"taylorOrder", this->taylorOrder},
		{"dimension", this->dimension},
		{"timeStepsForOutput", this->timeStepsForOutput},
		{"mainOutputFolder", fileTree["output"]["main"]},
		{"particleOutputFolder", fileTree["output"]["particle"]},
		{"boundaryOutputFolder", fileTree["output"]["boundary"]},
		{"interactions", fileTree["input"]["interaction"]},
		{"particles", fileTree["input"]["particle"]},
		{"boundaries", fileTree["input"]["boundary"]}
	}

	path mainOutputFilePath = fileTree["output"]["main"] / path("main.json");
	std::ofstream mainOutputFile( mainOutputFilePath.string() );
	mainOutputFile << mainOutput;

	for(json::iterator it = fileTree["input"]["interaction"].begin(); it != fileTree["input"]["interaction"].end(); ++it)
	{
		string interactionName = it.key();
		path interactionInputFilePath = it.value();

		json interactionInput = read_json(interactionInputFilePath.string());
		path interactionOutputFilePath = fileTree["output"]["main"] / path("interaction") / path(interactionName + ".json");
		std::ofstream interactionOutputFile(interactionOutputFilePath);
		interactionOutputFile << interactionInput;
	}

	for(json::iterator it = fileTree["input"]["particle"].begin(); it != fileTree["input"]["particle"].end(); ++it)
	{
		string particleName = it.key();
		path particleInputFilePath = it.value();

		json particleInput = read_json(particleInputFilePath.string());
		path particleOutputFilePath = fileTree["output"]["main"] / path("particle") / path(particleName + ".json");
		std::ofstream particleOutputFile(particleOutputFilePath);
		particleOutputFile << particleInput;
	}

	for(json::iterator it = fileTree["input"]["boundary"].begin(); it != fileTree["input"]["boundary"].end(); ++it)
	{
		string boundaryName = it.key();
		path boundaryInputFilePath = it.value();

		json boundaryInput = read_json(boundaryInputFilePath.string());
		path boundaryOutputFilePath = fileTree["output"]["main"] / path("boundary") / path(boundaryName + ".json");
		std::ofstream boundaryOutputFile(boundaryOutputFilePath);
		boundaryOutputFile << boundaryInput;
	}
}

namespace detail {

template<typename E>
struct open_entity_file
{
	template<T>
	void call(const T & entityVectorTuple, const path & entityFolder, std::map<string, unique_ptr<std::ofstream>> & entityFileMap)
	{
		for(auto entity : std::get< vector<E> >(entityVectorTuple))
		{
			path entityOutputPath = entityNode / path(entity.getName() + ".json");
			entityFileMap[entity.getName()] = make_unique<std::ofstream>(entityOutputPath.string());
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
>::openFiles()
{
	path timeVectorOutputFilePath = fileTree["output"]["main"] / path("timeVector.json");
	mainFileMap["timeVector"] = make_unique<std::ofstream>( timeVectorOutputFilePath.string() );

	mp::visit<ParticleList, detail::open_entity_file>::call_same(particles, fileTree["output"]["particle"], particleFileMap);
	mp::visit<BoundaryList, detail::open_entity_file>::call_same(boundaries, fileTree["output"]["boundary"], boundaryFileMap);
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

	for(double t = initialTime; t < finalTime; t += timeStep)
	{

	}
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
