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

#include <boost/type_index.hpp> // DEBUG

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
	SeekerList<BlindSeeker>
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
	this->looperToUse = j.at("looper");
	this->seekerToUse = j.at("seeker");

	fileTree["output"]["main"] = j.at("mainOutputFolder").get<path>();
	fileTree["output"]["particleDir"] = j.at("particleOutputFolder").get<path>();
	fileTree["output"]["boundaryDir"] = j.at("boundaryOutputFolder").get<path>();

	if(j.count("interactions") > 0) setupInteractions(j.at("interactions"));

	if(j.count("particles") > 0) buildParticles(j.at("particles"));

	if(j.count("boundaries") > 0) buildBoundaries(j.at("boundaries"));
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
	SeekerList<BlindSeeker>
>::setupInteractions(const json & interactionsJSON)
{
	std::cout << "Interactions setup" << std::endl; // DEBUG

	for(json::const_iterator it = interactionsJSON.begin(); it != interactionsJSON.end(); ++it) 
	{
		string interactionName(it.key());
		interactionsToUse.insert( interactionName );

		if(it->is_string())
		{
			path interactionInputFilePath = it.value();

			mp::for_each< mp::provide_indices<InteractionList> >(
			[&, this](auto Index)
			{
				using I = typename mp::get<Index, InteractionList>::type;
				if( NamedType<I>::name == interactionName )
				{
					json j = read_json(interactionInputFilePath.string());

					Builder<I>::setup(j.at(NamedType<I>::name));
				}
			});
			
			fileTree["input"]["interaction"][interactionName] = interactionInputFilePath;
		}
	}

	for(auto&& entry : interactionsToUse)
		std::cout << "Using interaction " << entry << std::endl; // DEBUG
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
	SeekerList<BlindSeeker>
>::buildParticles(const json & particlesJSON)
{
	std::cout << "Building particles" << std::endl; // DEBUG

	for(json::const_iterator it = particlesJSON.begin(); it != particlesJSON.end(); ++it) 
	{
		if(it->is_array())
		{
			for(const path particleInputFilePath : *it)
			{
				string particleType(it.key());
				string particleName;

				mp::for_each< mp::provide_indices<ParticleList> >(
				[&, this](auto Index)
				{
					using Particle = typename mp::get<Index, ParticleList>::type;
					if( NamedType<Particle>::name == particleType)
					{
						json j = read_json(particleInputFilePath.string());

						Particle particle = j;

						particleName = particle.getName();
						std::get< vector<Particle> >(particles).push_back( particle );
					}
				});

				fileTree["input"]["particle"][particleName] = particleInputFilePath;
			}
		}
		else if(it->is_string())
		{
			string particleType(it.key());
			string particleName;
			path particleInputFilePath = it.value();

			mp::for_each< mp::provide_indices<ParticleList> >(
			[&, this](auto Index)
			{
				using Particle = typename mp::get<Index, ParticleList>::type;
				if( NamedType<Particle>::name == particleType)
				{
					json j = read_json(particleInputFilePath.string());

					Particle particle = j;

					particleName = particle.getName();
					std::get< vector<Particle> >(particles).push_back( particle );
				}
			});

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
	SeekerList<BlindSeeker>
>::buildBoundaries(const json & boundariesJSON)
{
	std::cout << "Building boundaries" << std::endl; // DEBUG
	
	for(json::const_iterator it = boundariesJSON.begin(); it != boundariesJSON.end(); ++it) 
	{
		if(it->is_array())
		{
			for(const path boundaryInputFilePath : *it)
			{
				string boundaryType(it.key());
				string boundaryName;

				mp::for_each< mp::provide_indices<BoundaryList> >(
				[&, this](auto Index)
				{
					using Particle = typename mp::get<Index, BoundaryList>::type;
					if( NamedType<Particle>::name == boundaryType)
					{
						json j = read_json(boundaryInputFilePath.string());

						Particle particle = j;

						boundaryName = particle.getName();
						std::get< vector<Particle> >(boundaries).push_back( particle );
					}
				});

				fileTree["input"]["boundary"][boundaryName] = boundaryInputFilePath;
			}
		}
		else if(it->is_string())
		{
			string boundaryType(it.key());
			string boundaryName;
			path boundaryInputFilePath = it.value();

			mp::for_each< mp::provide_indices<BoundaryList> >(
			[&, this](auto Index)
			{
				using Particle = typename mp::get<Index, BoundaryList>::type;
				if( NamedType<Particle>::name == boundaryType)
				{
					json j = read_json(boundaryInputFilePath.string());

					Particle particle = j;

					boundaryName = particle.getName();
					std::get< vector<Particle> >(boundaries).push_back( particle );
				}
			});

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
	SeekerList<BlindSeeker>
>::createDirectories() const
{
	filesystem::create_directories( fileTree["output"]["main"] );
	filesystem::create_directories( fileTree["output"]["main"] / path("input") / path("particle"));
	filesystem::create_directories( fileTree["output"]["main"] / path("input") / path("boundary"));
	filesystem::create_directories( fileTree["output"]["main"] / path("input") / path("interaction"));
	filesystem::create_directories( fileTree["output"]["particleDir"] );
	filesystem::create_directories( fileTree["output"]["boundaryDir"] );
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
	SeekerList<BlindSeeker>
>::outputMainData()
{
	this->createDirectories();

	json mainOutput{
		{"initialTime", this->initialTime},
		{"timeStep", this->timeStep},
		{"finalTime", this->finalTime},
		{"taylorOrder", this->taylorOrder},
		{"dimension", this->dimension},
		{"timeStepsForOutput", this->timeStepsForOutput},
		{"outputsForExporting", this->outputsForExporting},
		{"looper", this->looperToUse},
		{"seeker", this->seekerToUse},
		{"mainOutputFolder", fileTree["output"]["main"]},
		{"particleOutputFolder", fileTree["output"]["particleDir"]},
		{"boundaryOutputFolder", fileTree["output"]["boundaryDir"]},
		{"interactions", fileTree["input"]["interaction"]},
		{"particles", fileTree["input"]["particle"]},
		{"boundaries", fileTree["input"]["boundary"]}
	};


	path mainOutputFilePath = fileTree["output"]["main"] / path("main.json");
	mainFileMap["main"] = make_unique<std::fstream>(mainOutputFilePath.string(), std::ios::in | std::ios::out | std::ios::trunc);
	*mainFileMap["main"] << mainOutput.dump(4);
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
	SeekerList<BlindSeeker>
>::backupInteractions() const
{
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
	SeekerList<BlindSeeker>
>::backupParticles() const
{
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
	SeekerList<BlindSeeker>
>::backupBoundaries() const
{
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

template<typename P>
struct open_particle_file
{
	template<typename T>
	static void call(const T & particleVectorTuple, json & fileTree, std::map<string, unique_ptr<std::fstream>> & particleFileMap)
	{
		path particleFolder = fileTree["output"]["particleDir"].get<path>();
		for(const auto& particle : std::get< vector<P> >(particleVectorTuple))
		{
			path particleOutputPath = particleFolder / path(particle.getName() + ".json");

			fileTree["output"]["particle"][particle.getName()] = particleOutputPath;
			particleFileMap[particle.getName()] = make_unique<std::fstream>(particleOutputPath.string(), std::ios::in | std::ios::out | std::ios::trunc);
			*particleFileMap[particle.getName()] << json().dump();
		}
	}
};

template<typename B>
struct open_boundary_file
{
	template<typename T>
	static void call(const T & boundaryVectorTuple, json & fileTree, std::map<string, unique_ptr<std::fstream>> & boundaryFileMap)
	{
		path boundaryFolder = fileTree["output"]["boundaryDir"].get<path>();
		for(const auto& boundary : std::get< vector<B> >(boundaryVectorTuple))
		{
			path boundaryOutputPath = boundaryFolder / path(boundary.getName() + ".json");

			fileTree["output"]["boundary"][boundary.getName()] = boundaryOutputPath;
			boundaryFileMap[boundary.getName()] = make_unique<std::fstream>(boundaryOutputPath.string(), std::ios::in | std::ios::out | std::ios::trunc);
			*boundaryFileMap[boundary.getName()] << json().dump();
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
	SeekerList<BlindSeeker>
>::openFiles()
{
	path timeVectorOutputFilePath = fileTree["output"]["main"] / path("timeVector.json");
	mainFileMap["timeVector"] = make_unique<std::fstream>(timeVectorOutputFilePath.string(), std::ios::in | std::ios::out | std::ios::trunc);
	*mainFileMap["timeVector"] << json().dump();

	mp::visit<ParticleList, detail::open_particle_file>::call_same(particles, fileTree, particleFileMap);
	mp::visit<BoundaryList, detail::open_boundary_file>::call_same(boundaries, fileTree, boundaryFileMap);
}

namespace detail {

template<typename P>
struct write_particles_to_json
{
	template<typename ParticleTuple, typename Time>
	static void call(const ParticleTuple & particleVectorTuple, std::map<string, vector<json>>& particleJsonMap, const Time & time)
	{
		for(auto&& particle : std::get< vector<P> >(particleVectorTuple))
		{
			json j{
				{time.getIndexTag(), time.getIndex()},
				{"particleType", NamedType<P>::name},
				{"particle", particle}
			};
			particleJsonMap[particle.getName()].push_back(j);
		}
	}
};

template<typename B>
struct write_boundaries_to_json
{
	template<typename BoundaryTuple, typename Time>
	static void call(const BoundaryTuple & boundaryVectorTuple, std::map<string, vector<json>>& boundaryJsonMap, const Time & time)
	{
		for(auto&& boundary : std::get< vector<B> >(boundaryVectorTuple))
		{
			json j{
				{time.getIndexTag(), time.getIndex()},
				{"boundaryType", NamedType<B>::name},
				{"boundary", boundary}
			};
			boundaryJsonMap[boundary.getName()].push_back(j);
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
		for(auto& boundary : std::get<vector<B>>(boundaryVectorTuple))
		{
			boundary.update(time);
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
			auto acceleration = particle.getResultingForce() / particle.template get<Mass>();
			auto angularAcceleration = particle.getResultingTorque() / particle.template get<MomentOfInertia>();

			vector<Vector3D> correctedPosition = Interaction<>::gearCorrector(
					particle.getPositionMatrix(),
					acceleration,
					particle.getTaylorOrder(),
					time.getTimeStep()
				);
			particle.setPositionMatrix(correctedPosition);

			vector<Vector3D> correctedOrientation = Interaction<>::gearCorrector(
					particle.getOrientationMatrix(),
					angularAcceleration,
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
struct interact_particle_particle
{
	template<typename ParticleVectorTuple, typename Time>
	static void call(ParticleVectorTuple & particleVectorTuple, const Time & time, const std::set< std::string > & interactionsToUse)
	{
		using InteractionType = typename mp::get<0, InteractionTriplet>::type;
		using EntityType = typename mp::get<1, InteractionTriplet>::type;
		using NeighborType = typename mp::get<2, InteractionTriplet>::type;

		if(interactionsToUse.count(NamedType<InteractionType>::name) > 0) // check at runtime that this interaction should be used
		{
			if(std::is_same<EntityType, NeighborType>::value)
			{
				for(auto&& entity_it = std::get<vector<EntityType>>(particleVectorTuple).begin();
					entity_it != std::get<vector<EntityType>>(particleVectorTuple).end();
					++entity_it)
				{
					for(auto&& neighbor_it = std::next(entity_it);
						neighbor_it != std::get<vector<EntityType>>(particleVectorTuple).end();
						++neighbor_it)
					{
						InteractionType::calculate(*entity_it, *neighbor_it, time);
					}
				}
			}
			else
			{
				for(auto& entity : std::get<vector<EntityType>>(particleVectorTuple))
				{
					for(auto& neighbor : std::get<vector<NeighborType>>(particleVectorTuple))
					{
						InteractionType::calculate(entity, neighbor, time);
					}
				}
			}
		}
	}
};

template<typename InteractionTriplet>
struct interact_particle_boundary
{
	template<typename ParticleVectorTuple, typename BoundaryVectorTuple, typename Time>
	static void call(ParticleVectorTuple & particleVectorTuple, BoundaryVectorTuple & boundaryVectorTuple, const Time & time, const std::set< std::string > & interactionsToUse)
	{
		using InteractionType = typename mp::get<0, InteractionTriplet>::type;
		using EntityType = typename mp::get<1, InteractionTriplet>::type;
		using NeighborType = typename mp::get<2, InteractionTriplet>::type;

		for(auto& entity : std::get<vector<EntityType>>(particleVectorTuple))
		{
			for(auto& neighbor : std::get<vector<NeighborType>>(boundaryVectorTuple))
			{
				if(interactionsToUse.count(NamedType<InteractionType>::name) > 0)
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
template<typename Time>
void Simulation<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::exportTime(const Time & time)
{
	json fileContent;
	json informationToExport{
		time.as_json()
	};

	path filepath = fileTree["output"]["main"] / path("timeVector.json");
	mainFileMap["timeVector"]->seekg(0); // rewinds the file
	*mainFileMap["timeVector"] >> fileContent;
	mainFileMap["timeVector"]->close();

	mainFileMap["timeVector"]->open(filepath.string(), std::ios::in | std::ios::out | std::ios::trunc);
	*mainFileMap["timeVector"] << merge(fileContent, informationToExport).dump(4);
}

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
template<typename Time>
void Simulation<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::exportParticles(const Time & time)
{
	for(auto&& it = particleJsonMap.begin(); it != particleJsonMap.end(); ++it)
	{
		json fileContent;
		json informationToExport = it->second;

		path filepath = fileTree["output"]["particle"][it->first].get<path>();
		particleFileMap[it->first]->seekg(0); // rewinds the file
		*particleFileMap[it->first] >> fileContent;
		particleFileMap[it->first]->close();

		particleFileMap[it->first]->open(filepath.string(), std::ios::in | std::ios::out | std::ios::trunc);
		*particleFileMap[it->first] << merge(fileContent, informationToExport).dump(4);

		it->second.clear();
	}
}

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
template<typename Time>
void Simulation<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::exportBoundaries(const Time & time)
{
	for(auto&& it = boundaryJsonMap.begin(); it != boundaryJsonMap.end(); ++it)
	{
		json fileContent;
		json informationToExport = it->second;

		path filepath = fileTree["output"]["boundary"][it->first].get<path>();
		boundaryFileMap[it->first]->seekg(0); // rewinds the file
		*boundaryFileMap[it->first] >> fileContent;
		boundaryFileMap[it->first]->close();

		boundaryFileMap[it->first]->open(filepath.string(), std::ios::in | std::ios::out | std::ios::trunc);
		*boundaryFileMap[it->first] << merge(fileContent, informationToExport).dump(4);

		it->second.clear();
	}
}

template<typename InteractionTriplet>
struct print_check
{
	static void call()
	{
		using InteractionType = typename mp::get<0, InteractionTriplet>::type;
		using EntityType = typename mp::get<1, InteractionTriplet>::type;
		using NeighborType = typename mp::get<2, InteractionTriplet>::type;

		std::cout << "Interaction: " 
			<< boost::typeindex::type_id_with_cvr<InteractionType>().pretty_name() 
			<< std::endl; // DEBUG

		std::cout << "EntityType: " 
			<< boost::typeindex::type_id_with_cvr<EntityType>().pretty_name() 
			<< std::endl; // DEBUG

		std::cout << "NeighborType: " 
			<< boost::typeindex::type_id_with_cvr<NeighborType>().pretty_name() 
			<< std::endl; // DEBUG

		std::cout << "Check: "
			<< std::boolalpha
			<< InteractionType::template check<EntityType, NeighborType>::value 
			<< std::endl;

		std::cout << std::endl;
	}
};	// DEBUG

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
	SeekerList<BlindSeeker>
>::simulate()
{
	openFiles();

	GearLooper::Time<std::size_t, double> time{initialTime, timeStep, finalTime};

	unsigned long timeStepsForOutputCounter = 0;
	unsigned long outputsForExportingCounter = 0;

	// ---- DEBUG ----
	mp::visit< typename mp::combinatory::generate_combination_list<
		InteractionList,
		ParticleList,
		ParticleList
	>::type , print_check>::call_same();
	mp::visit< typename mp::combinatory::generate_combination_list<
		InteractionList,
		ParticleList,
		BoundaryList
	>::type , print_check>::call_same();
	// ---- ----- ----

	std::cout << "ParticleList:\n" 
		<< boost::typeindex::type_id_with_cvr<ParticleList>().pretty_name() 
		<< std::endl; // DEBUG

	std::cout << "BoundaryList:\n" 
		<< boost::typeindex::type_id_with_cvr<BoundaryList>().pretty_name() 
		<< std::endl; // DEBUG

	std::cout << "InteractionList:\n" 
		<< boost::typeindex::type_id_with_cvr<InteractionList>().pretty_name() 
		<< std::endl; // DEBUG

	std::cout << "InteractionParticleParticleTriplets:\n" 
		<< boost::typeindex::type_id_with_cvr<InteractionParticleParticleTriplets>().pretty_name() 
		<< std::endl; // DEBUG

	for(time.start(); !time.end(); time.update())
	{
		std::cout << time.as_json() << std::endl; // DEBUG
		// Output
		if(timeStepsForOutputCounter == 0)
		{
			mp::visit<ParticleList, detail::write_particles_to_json>::call_same(particles, particleJsonMap, time);
			mp::visit<BoundaryList, detail::write_boundaries_to_json>::call_same(boundaries, boundaryJsonMap, time);

			if(outputsForExportingCounter == 0)
			{
				exportTime(time);
				exportParticles(time);
				exportBoundaries(time);
			}
			outputsForExportingCounter = (outputsForExportingCounter + 1) % outputsForExporting;
		}
		timeStepsForOutputCounter = (timeStepsForOutputCounter + 1) % timeStepsForOutput;

		mp::visit<ParticleList, detail::initialize_particle>::call_same(particles);
		mp::visit<ParticleList, detail::predict_particle>::call_same(particles, time);
		mp::visit<BoundaryList, detail::update_boundary>::call_same(boundaries, time);

		mp::visit<InteractionParticleParticleTriplets, detail::interact_particle_particle>::call_same(
				particles, time, interactionsToUse
			);
		mp::visit<InteractionParticleBoundaryTriplets, detail::interact_particle_boundary>::call_same(
				particles, boundaries, time, interactionsToUse
			);

		mp::visit<ParticleList, detail::correct_particle>::call_same(particles, time);
	}
}

} // psin

#endif // SIMULATION_TPP
