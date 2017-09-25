#ifndef SIMULATION_TPP
#define SIMULATION_TPP

// JSONLib
#include <json.hpp>

// SimulationLib
#include <CommandLineParser.hpp>

// UtilsLib
#include <FileSystem.hpp>
#include <NamedType.hpp>
#include <mp/visit.hpp>

// Standard
#include <fstream>
#include <tuple>

namespace psin {

template<typename>
struct Builder;

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
>::setup(const path & mainInputFilePath)
{
	fileTree["input"]["main"] = mainInputFilePath;

	json j = read_json(fileTree["input"]["main"]);

	this->initialTime = j.at("initialTime");
	this->timeStep = j.at("timeStep");
	this->finalTime = j.at("finalTime");
	this->taylorOrder = j.at("taylorOrder");
	this->dimension = j.at("dimension");
	this->timeStepsForOutput = j.at("timeStepsForOutput");
	this->outputsForExporting = j.at("outputsForExporting");

	fileTree["output"]["main"] = j.at("mainOutputFolder").get<path>();
	fileTree["output"]["particle"] = j.at("particleOutputFolder").get<path>();
	fileTree["output"]["boundary"] = j.at("boundaryOutputFolder").get<path>();

	if(j.count("interactions") > 0) setupInteractions(j.at("interactions"));

	if(j.count("particles") > 0) buildParticles(j.at("particles"));

	if(j.count("boundaries") > 0) buildBoundaries(j.at("boundaries"));
}

namespace detail {

template<typename I>
struct conditionally_setup_interaction
{
	static void call(const string & interactionName, const path & filepath)
	{
		if( NamedType<I>::name == interactionName )
		{
			json j = read_json(filepath.string());

			Builder<I>::setup(j.at(NamedType<I>::name));
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
>::setupInteractions(const json & interactionsJSON)
{
	for(json::const_iterator it = interactionsJSON.begin(); it != interactionsJSON.end(); ++it) 
	{
		if(it->is_string())
		{
			string interactionName(it.key());
			path interactionInputFilePath = it.value();

			interactionsToUse.insert( interactionName );
			mp::visit<InteractionList, detail::conditionally_setup_interaction>::call_same(interactionName, interactionInputFilePath);
			fileTree["input"]["interaction"][interactionName] = interactionInputFilePath;
		}
	}
}

namespace detail {

template<typename Entity>
struct conditionally_build_entity
{
	template<typename EntityTuple>
	static void call(const string & entityType, const path & filepath, EntityTuple & entities, string & entityName)
	{
		if( NamedType<Entity>::name == entityType)
		{
			json j = read_json(filepath.string());

			Entity entity = j;

			entityName = entity.getName();
			std::get< vector<Entity> >(entities).push_back( entity );
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
>::buildParticles(const json & particlesJSON)
{
	for(json::const_iterator it = particlesJSON.begin(); it != particlesJSON.end(); ++it) 
	{
		if(it->is_array())
		{
			for(const path particleInputFilePath : *it)
			{
				string particleType(it.key());
				string particleName;

				mp::visit<ParticleList, detail::conditionally_build_entity>::call_same(particleType, particleInputFilePath, particles, particleName);

				fileTree["input"]["particle"][particleName] = particleInputFilePath;
			}
		}
		else if(it->is_string())
		{
			string particleType(it.key());
			string particleName;
			path particleInputFilePath = it.value();

			mp::visit<ParticleList, detail::conditionally_build_entity>::call_same(particleType, particleInputFilePath, particles, particleName);
			fileTree["input"]["particle"][particleName] = particleInputFilePath;
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
>::buildBoundaries(const json & boundariesJSON)
{
	for(json::const_iterator it = boundariesJSON.begin(); it != boundariesJSON.end(); ++it) 
	{
		if(it->is_array())
		{
			for(const path boundaryInputFilePath : *it)
			{
				string boundaryType(it.key());
				string boundaryName;

				mp::visit<BoundaryList, detail::conditionally_build_entity>::call_same(boundaryType, boundaryInputFilePath, boundaries, boundaryName);
				fileTree["input"]["boundary"][boundaryName] = boundaryInputFilePath;
			}
		}
		else if(it->is_string())
		{
			string boundaryType(it.key());
			string boundaryName;
			path boundaryInputFilePath = it.value();

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
>::outputMainData() const
{
	filesystem::create_directories( fileTree["output"]["main"] );
	filesystem::create_directories( fileTree["output"]["main"] / path("input") / path("particle"));
	filesystem::create_directories( fileTree["output"]["main"] / path("input") / path("boundary"));
	filesystem::create_directories( fileTree["output"]["main"] / path("input") / path("interaction"));
	filesystem::create_directories( fileTree["output"]["particle"] );
	filesystem::create_directories( fileTree["output"]["boundary"] );

	json mainOutput{
		{"initialTime", this->initialTime},
		{"timeStep", this->timeStep},
		{"finalTime", this->finalTime},
		{"taylorOrder", this->taylorOrder},
		{"dimension", this->dimension},
		{"timeStepsForOutput", this->timeStepsForOutput},
		{"outputsForExporting", this->outputsForExporting},
		{"mainOutputFolder", fileTree["output"]["main"]},
		{"particleOutputFolder", fileTree["output"]["particle"]},
		{"boundaryOutputFolder", fileTree["output"]["boundary"]},
		{"interactions", fileTree["input"]["interaction"]},
		{"particles", fileTree["input"]["particle"]},
		{"boundaries", fileTree["input"]["boundary"]}
	};


	path mainOutputFilePath = fileTree["output"]["main"] / path("main.json");
	std::ofstream mainOutputFile( mainOutputFilePath.string() );
	mainOutputFile << mainOutput.dump(4);

	if(fileTree["input"]["interaction"].is_object())
	{	
		for(json::const_iterator it = fileTree["input"]["interaction"].begin(); it != fileTree["input"]["interaction"].end(); ++it)
		{
			string interactionName = it.key();
			path interactionInputFilePath = it.value();

			json interactionInput = read_json(interactionInputFilePath.string());
			path interactionOutputFilePath = fileTree["output"]["main"] / path("input") / path("interaction") / path(interactionName + ".json");
			std::ofstream interactionOutputFile(interactionOutputFilePath.string());
			interactionOutputFile << interactionInput.dump(4);
		}
	}

	if(fileTree["input"]["particle"].is_object())
	{	
		for(json::const_iterator it = fileTree["input"]["particle"].begin(); it != fileTree["input"]["particle"].end(); ++it)
		{
			string particleName = it.key();
			path particleInputFilePath = it.value();

			json particleInput = read_json(particleInputFilePath.string());
			path particleOutputFilePath = fileTree["output"]["main"] / path("input") / path("particle") / path(particleName + ".json");
			std::ofstream particleOutputFile(particleOutputFilePath.string());
			particleOutputFile << particleInput.dump(4);
		}
	}

	if(fileTree["input"]["boundary"].is_object())
	{	
		for(json::const_iterator it = fileTree["input"]["boundary"].begin(); it != fileTree["input"]["boundary"].end(); ++it)
		{
			string boundaryName = it.key();
			path boundaryInputFilePath = it.value();

			json boundaryInput = read_json(boundaryInputFilePath.string());
			path boundaryOutputFilePath = fileTree["output"]["main"] / path("input") / path("boundary") / path(boundaryName + ".json");
			std::ofstream boundaryOutputFile(boundaryOutputFilePath.string());
			boundaryOutputFile << boundaryInput.dump(4);
		}
	}
}

namespace detail {

template<typename E>
struct open_entity_file
{
	template<typename T>
	static void call(const T & entityVectorTuple, const path & entityFolder, std::map<string, unique_ptr<std::fstream>> & entityFileMap)
	{
		for(const auto& entity : std::get< vector<E> >(entityVectorTuple))
		{
			path entityOutputPath = entityFolder / path(entity.getName() + ".json");

			entityFileMap[entity.getName()] = make_unique<std::fstream>(entityOutputPath.string(), std::ios::in | std::ios::out | std::ios::trunc);
			*entityFileMap[entity.getName()] << json().dump();
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
	mainFileMap["timeVector"] = make_unique<std::fstream>( timeVectorOutputFilePath.string() );

	path particleFolder = fileTree["output"]["particle"].get<path>();
	path boundaryFolder = fileTree["output"]["boundary"].get<path>();

	mp::visit<ParticleList, detail::open_entity_file>::call_same(particles, particleFolder, particleFileMap);
	mp::visit<BoundaryList, detail::open_entity_file>::call_same(boundaries, boundaryFolder, boundaryFileMap);
}

namespace detail {

template<typename E>
struct write_entities_to_json
{
	template<typename EntityTuple>
	static void call(const EntityTuple & entityVectorTuple, std::map<string, vector<json>>& entityJsonMap)
	{
		for(auto&& entity : std::get< vector<E> >(entityVectorTuple))
		{
			entityJsonMap[entity.getName()].push_back(entity);
		}
	}
};

template<typename P>
struct predict_particle
{
	template<typename ParticleTuple, typename Time>
	static void call(ParticleTuple & particleVectorTuple, const Time & time)
	{
		for(auto& particle : std::get<vector<P>>(particleVectorTuple))
		{
			vector<Vector3D> predictedPosition = Interaction<>::taylorPredictor(
					particle.getPositionMatrix(),
					particle.getTaylorOrder(),
					time.getTimeStep()
				);
			particle.setPositionMatrix(predictedPosition);

			vector<Vector3D> predictedOrientation = Interaction<>::taylorPredictor(
					particle.getOrientationMatrix(),
					particle.getTaylorOrder(),
					time.getTimeStep()
				);
			particle.setOrientationMatrix(predictedOrientation);
		}
	}
};

template<typename B>
struct update_boundary
{
	template<typename BoundaryVectorTuple, typename Time>
	static void call(BoundaryVectorTuple & boundaryVectorTuple, const Time & time)
	{
		for(auto& boundary : std::get<B>(boundaryVectorTuple))
		{
			boundary.updatePosition(time);
			boundary.updateOrientation(time);
		}
	}
};

template<typename P>
struct correct_particle
{
	template<typename ParticleTuple, typename Time>
	static void call(ParticleTuple & particleVectorTuple, const Time & time)
	{
		for(auto& particle : std::get<vector<P>>(particleVectorTuple))
		{
			vector<Vector3D> correctedPosition = Interaction<>::gearCorrector(
					particle.getPositionMatrix(),
					particle.getAcceleration(),
					particle.getTaylorOrder(),
					time.getTimeStep()
				);
			particle.setPositionMatrix(correctedPosition);

			vector<Vector3D> correctedOrientation = Interaction<>::gearCorrector(
					particle.getOrientationMatrix(),
					particle.getAngularAcceleration(),
					particle.getTaylorOrder(),
					time.getTimeStep()
				);
			particle.setOrientationMatrix(correctedOrientation);
		}
	}
};

template<typename P>
struct initialize_particle
{
	template<typename ParticleTuple>
	static void call(ParticleTuple & particleVectorTuple)
	{
		for(auto& particle : std::get<vector<P>>(particleVectorTuple))
		{
			particle.setBodyForce( nullVector3D() );
			particle.setContactForce( nullVector3D() );
			particle.setResultingTorque( nullVector3D() );
		}
	}
};

template<typename InteractionTriplet>
struct interact
{
	template<typename EntityVectorTuple, typename Time>
	static void call(EntityVectorTuple & entityVectorTuple, const Time & time, const std::set< std::string > & interactionsToUse)
	{
		using InteractionType = typename mp::get<0, InteractionTriplet>::type;
		using EntityType = typename mp::get<1, InteractionTriplet>::type;
		using NeighborType = typename mp::get<2, InteractionTriplet>::type;

		for(auto& entity : std::get<EntityType>(entityVectorTuple))
		{
			for(auto& neighbor : std::get<NeighborType>(entityVectorTuple))
			{
				if(interactionsToUse.count(NamedType<InteractionTriplet>::name) > 0)
				{
					InteractionType::calculate(entity, neighbor, time);
				}
			}
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
>::simulate()
{
	openFiles();

	GearLooper::Time<unsigned long, double> time{initialTime, timeStep, finalTime};

	unsigned long timeStepsForOutputCounter = 0;
	unsigned long outputsForExportingCounter = 0;

	for(time.start(); !time.end(); time.update())
	{
		// Output
		if(timeStepsForOutputCounter == 0)
		{
			mp::visit<ParticleList, detail::write_entities_to_json>::call_same(particles, particleJsonMap);
			mp::visit<BoundaryList, detail::write_entities_to_json>::call_same(boundaries, boundaryJsonMap);

			if(outputsForExportingCounter == 0)
			{
				string timeIndex = to_string(time.getIndex());
				for(auto&& it = particleJsonMap.begin(); it != particleJsonMap.end(); ++it)
				{
					json fileContent;
					json informationToExport{
						{timeIndex, merge(it->second)}
					};

					particleFileMap[it->first]->seekg(0); // rewinds the file
					*particleFileMap[it->first] >> fileContent;

					*particleFileMap[it->first] << merge(fileContent, informationToExport).dump(4);
					it->second.clear();
				}
				for(auto&& it = boundaryJsonMap.begin(); it != boundaryJsonMap.end(); ++it)
				{
					json fileContent;
					json informationToExport{
						{timeIndex, merge(it->second)}
					};

					particleFileMap[it->first]->seekg(0); // rewinds the file
					*boundaryFileMap[it->first] >> fileContent;
					*boundaryFileMap[it->first] << merge(fileContent, informationToExport).dump(4);
					it->second.clear();
				}
			}
			outputsForExportingCounter = (outputsForExportingCounter + 1) % outputsForExporting;
		}
		timeStepsForOutputCounter = (timeStepsForOutputCounter + 1) % timeStepsForOutput;

		mp::visit<ParticleList, detail::initialize_particle>::call_same(particles);
		mp::visit<ParticleList, detail::predict_particle>::call_same(particles, time);
		mp::visit<BoundaryList, detail::update_boundary>::call_same(boundaries, time);

		// mp::visit<InteractionTriplets, detail::interact>::call_same(
		// 		std::tuple_cat(particles, boundaries), time, interactionsToUse
		// 	);

		mp::visit<ParticleList, detail::correct_particle>::call_same(particles, time);
	}
}

} // psin

#endif // SIMULATION_TPP
