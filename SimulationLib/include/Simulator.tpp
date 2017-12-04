#ifndef SIMULATOR_TPP
#define SIMULATOR_TPP

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

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulator<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::setup(const path & mainInputFilePath)
{
	fileTree["input"]["main"] = mainInputFilePath;

	json j = read_json(fileTree["input"]["main"]);

	this->initialInstant = j.at("InitialInstant");
	this->timeStep = j.at("TimeStep");
	this->finalInstant = j.at("FinalInstant");
	this->stepsForStoring = j.at("StepsForStoring");
	this->storagesForWriting = j.at("StoragesForWriting");
	this->looperToUse = j.at("Looper");
	this->seekerToUse = j.at("Seeker");
	if(j.count("PrintTime") > 0) this->printTime = j.at("PrintTime");

	fileTree["output"]["main"] = j.at("MainOutputFolder").get<path>();
	fileTree["output"]["particleDir"] = j.at("ParticleOutputFolder").get<path>();
	fileTree["output"]["boundaryDir"] = j.at("BoundaryOutputFolder").get<path>();

	if(j.count("Interactions") > 0) setupInteractions(j.at("Interactions"));

	if(j.count("Particles") > 0) buildParticles(j.at("Particles"));

	if(j.count("Boundaries") > 0) buildBoundaries(j.at("Boundaries"));
}


template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulator<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::setupInteractions(const json & interactionsJSON)
{
	std::cout << "Interactions setup" << std::endl; // DEBUG

	if(interactionsJSON.is_object())
	{
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

						initializeInteraction<I>(j.at(NamedType<I>::name));
					}
				});
				
				fileTree["input"]["interaction"][interactionName] = interactionInputFilePath;
			}
			else if(it->is_object())
			{
				mp::for_each< mp::provide_indices<InteractionList> >(
				[&, this](auto Index)
				{
					using I = typename mp::get<Index, InteractionList>::type;
					if( NamedType<I>::name == interactionName )
					{
						initializeInteraction<I>(it.value());
					}
				});
				
				fileTree["input"]["interaction"][interactionName] = fileTree["input"]["main"];
			}
		}
	}
	else if(interactionsJSON.is_string())
	{
		string interactionName = interactionsJSON.get<string>();
		interactionsToUse.insert( interactionName );		
		fileTree["input"]["interaction"][interactionName] = fileTree["input"]["main"];
	}
	else if(interactionsJSON.is_array())
	{
		for(auto&& interactionJSON : interactionsJSON)
		{
			if(interactionJSON.is_string())
			{
				string interactionName = interactionJSON.get<string>();
				interactionsToUse.insert( interactionName );		
				fileTree["input"]["interaction"][interactionName] = fileTree["input"]["main"];
			}
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
void Simulator<
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
			for(json particleEntry : *it)
			{
				string particleType(it.key());
				string particleName;
				path particleInputFilePath = fileTree["input"]["main"];

				mp::for_each< mp::provide_indices<ParticleList> >(
				[&, this](auto Index)
				{
					using Particle = typename mp::get<Index, ParticleList>::type;
					if( NamedType<Particle>::name == particleType)
					{
						if(particleEntry.is_string()) // Considered input file
						{
							particleInputFilePath = particleEntry.get<string>();
							particleEntry = read_json(particleInputFilePath.string());
						}

						Particle particle = particleEntry;

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
		else if(it->is_object())
		{
			string particleType(it.key());
			string particleName;
			path particleInputFilePath = fileTree["input"]["main"].get<string>();

			mp::for_each< mp::provide_indices<ParticleList> >(
			[&, this](auto Index)
			{
				using Particle = typename mp::get<Index, ParticleList>::type;
				if( NamedType<Particle>::name == particleType)
				{
					Particle particle = it.value();

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
void Simulator<
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
			for(json boundaryEntry : *it)
			{
				string boundaryType(it.key());
				string boundaryName;
				path boundaryInputFilePath = fileTree["input"]["main"];

				mp::for_each< mp::provide_indices<BoundaryList> >(
				[&, this](auto Index)
				{
					using Boundary = typename mp::get<Index, BoundaryList>::type;
					if( NamedType<Boundary>::name == boundaryType)
					{
						if(boundaryEntry.is_string()) // Considered input file
						{
							boundaryInputFilePath = boundaryEntry.get<string>();
							boundaryEntry = read_json(boundaryInputFilePath.string());
						}

						Boundary boundary = boundaryEntry;

						boundaryName = boundary.getName();
						std::get< vector<Boundary> >(boundaries).push_back( boundary );
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
				using Boundary = typename mp::get<Index, BoundaryList>::type;
				if( NamedType<Boundary>::name == boundaryType)
				{
					json j = read_json(boundaryInputFilePath.string());

					Boundary boundary = j;

					boundaryName = boundary.getName();
					std::get< vector<Boundary> >(boundaries).push_back( boundary );
				}
			});

			fileTree["input"]["boundary"][boundaryName] = boundaryInputFilePath;
		}
		else if(it->is_object())
		{
			string boundaryType(it.key());
			string boundaryName;
			path boundaryInputFilePath = fileTree["input"]["main"].get<string>();

			mp::for_each< mp::provide_indices<BoundaryList> >(
			[&, this](auto Index)
			{
				using Boundary = typename mp::get<Index, BoundaryList>::type;
				if( NamedType<Boundary>::name == boundaryType)
				{
					Boundary boundary = it.value();

					boundaryName = boundary.getName();
					std::get< vector<Boundary> >(boundaries).push_back( boundary );
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
void Simulator<
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
void Simulator<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::outputMainData()
{
	this->createDirectories();

	json mainOutput{
		{"InitialInstant", this->initialInstant},
		{"TimeStep", this->timeStep},
		{"FinalInstant", this->finalInstant},
		{"StepsForStoring", this->stepsForStoring},
		{"StoragesForWriting", this->storagesForWriting},
		{"Looper", this->looperToUse},
		{"Seeker", this->seekerToUse},
		{"PrintTime", this->printTime},
		{"MainOutputFolder", fileTree["output"]["main"]},
		{"ParticleOutputFolder", fileTree["output"]["particleDir"]},
		{"BoundaryOutputFolder", fileTree["output"]["boundaryDir"]},
		{"Interactions", fileTree["input"]["interaction"]},
		{"Particles", fileTree["input"]["particle"]},
		{"Boundaries", fileTree["input"]["boundary"]}
	};


	path mainOutputFilePath = fileTree["output"]["main"] / path("main.json");
	mainFileMap["main"] = make_unique<std::fstream>(mainOutputFilePath.string(), std::ios::in | std::ios::out | std::ios::trunc);
	*mainFileMap["main"] << mainOutput.dump(4) << std::flush;
}

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulator<
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
void Simulator<
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
void Simulator<
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
void Simulator<
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

template<typename Ofstream>
Ofstream& operator<<(Ofstream& out, const vector<Vector3D> & v)// DEBUG
{
	for(auto&& entry : v)
	{
		out << entry << std::endl;
	}

	return out;
}

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

			auto correctedPosition = Interaction<>::gearCorrector(
					particle.getPositionMatrix(),
					acceleration,
					2,
					particle.getTaylorOrder(),
					time.getTimeStep()
				);
			particle.setPositionMatrix(correctedPosition);

			if constexpr(is_spherical<P>::value)
			{
				auto orientation = particle.getOrientation();
				auto orientationMatrix = particle.getOrientationMatrix();

				// std::cout << "Particle name: " << particle.getName() << "-----------------" << std::endl; // DEBUG

				// std::cout << "Orientation Matrix:\n" << orientationMatrix << std::endl; // DEBUG

				orientationMatrix.erase(orientationMatrix.begin());

				// std::cout << "Orientation Matrix after erasing orientation:\n" << orientationMatrix << std::endl; // DEBUG
				// std::cout << "Angular acceleration: " << angularAcceleration << std::endl; // DEBUG


				auto correctedOrientation = Interaction<>::gearCorrector(
						orientationMatrix,
						angularAcceleration,
						1,
						particle.getTaylorOrder()-1,
						time.getTimeStep()
					);

				// std::cout << "Corrected Orientation Matrix:\n" << correctedOrientation << std::endl; // DEBUG

				correctedOrientation.insert(correctedOrientation.begin(), orientation);

				// std::cout << "Corrected Orientation Matrix after inserting orientation:\n" << correctedOrientation << std::endl; // DEBUG

				particle.setOrientationMatrix(correctedOrientation);
			}
			else
			{
				vector<Vector3D> correctedOrientation = Interaction<>::gearCorrector(
						particle.getOrientationMatrix(),
						angularAcceleration,
						2,
						particle.getTaylorOrder(),
						time.getTimeStep()
					);
				particle.setOrientationMatrix(correctedOrientation);
			}
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

		if(interactionsToUse.count(NamedType<InteractionType>::name) > 0)
		{
			for(auto& entity : std::get<vector<EntityType>>(particleVectorTuple))
			{
				for(auto& neighbor : std::get<vector<NeighborType>>(boundaryVectorTuple))
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
void Simulator<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::exportTime()
{
	json fileContent;

	path filepath = fileTree["output"]["main"] / path("timeVector.json");
	mainFileMap["timeVector"]->seekg(0); // rewinds the file
	*mainFileMap["timeVector"] >> fileContent;
	mainFileMap["timeVector"]->close();

	mainFileMap["timeVector"]->open(filepath.string(), std::ios::in | std::ios::out | std::ios::trunc);
	*mainFileMap["timeVector"] << merge(std::move(fileContent), timeJsonVector).dump(4) << std::flush;

	timeJsonVector.clear();
}

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulator<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::exportParticles()
{
	for(auto&& it = particleJsonMap.begin(); it != particleJsonMap.end(); ++it)
	{
		json fileContent;

		path filepath = fileTree["output"]["particle"][it->first].get<path>();
		particleFileMap[it->first]->seekg(0); // rewinds the file
		*particleFileMap[it->first] >> fileContent;
		particleFileMap[it->first]->close();

		particleFileMap[it->first]->open(filepath.string(), std::ios::in | std::ios::out | std::ios::trunc);
		*particleFileMap[it->first] << merge(std::move(fileContent), it->second).dump(4) << std::flush;

		it->second.clear();
	}
}

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulator<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::exportBoundaries()
{
	for(auto&& it = boundaryJsonMap.begin(); it != boundaryJsonMap.end(); ++it)
	{
		json fileContent;

		path filepath = fileTree["output"]["boundary"][it->first].get<path>();
		boundaryFileMap[it->first]->seekg(0); // rewinds the file
		*boundaryFileMap[it->first] >> fileContent;
		boundaryFileMap[it->first]->close();

		boundaryFileMap[it->first]->open(filepath.string(), std::ios::in | std::ios::out | std::ios::trunc);
		*boundaryFileMap[it->first] << merge(std::move(fileContent), it->second).dump(4) << std::flush;

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
			<< std::endl; // DEBUG

		std::cout << std::endl; // DEBUG
	}
};	// DEBUG

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulator<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::simulate()
{
	openFiles();

	GearLooper::Time<std::size_t, double> time{initialInstant, timeStep, finalInstant};

	unsigned long stepsForStoringCounter = 0;
	unsigned long storagesForWritingCounter = 0;

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

	std::cout << "InteractionParticleBoundaryTriplets:\n" 
		<< boost::typeindex::type_id_with_cvr<InteractionParticleBoundaryTriplets>().pretty_name() 
		<< std::endl; // DEBUG

	for(time.start(); !time.end(); time.update())
	{
		if(this->printTime) std::cout << time.as_json() << std::endl;

		// Output
		if(stepsForStoringCounter == 0)
		{
			timeJsonVector.push_back(time.as_json());
			mp::visit<ParticleList, detail::write_particles_to_json>::call_same(particles, particleJsonMap, time);
			mp::visit<BoundaryList, detail::write_boundaries_to_json>::call_same(boundaries, boundaryJsonMap, time);

			if(storagesForWritingCounter == 0)
			{
				exportTime();
				exportParticles();
				exportBoundaries();
			}
			storagesForWritingCounter = (storagesForWritingCounter + 1) % storagesForWriting;
		}
		stepsForStoringCounter = (stepsForStoringCounter + 1) % stepsForStoring;

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

	this->endSimulation(time);
}
template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
void Simulator<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::printSuccessMessage() const
{
	std::cout << "Finished." << std::endl; // DEBUG
}

template<typename I>
void finalizeInteraction();

template<
	typename ... ParticleTypes,
	typename ... BoundaryTypes,
	typename ... InteractionTypes
>
template<typename Time>
void Simulator<
	ParticleList<ParticleTypes...>,
	BoundaryList<BoundaryTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<BlindSeeker>
>::endSimulation(const Time & time)
{
	exportTime();
	exportParticles();
	exportBoundaries();

	mp::for_each< mp::provide_indices<InteractionList> >(
	[&, this](auto Index)
	{
		using I = typename mp::get<Index, InteractionList>::type;
		psin::finalizeInteraction<I>();
	});

	this->printSuccessMessage();
}

} // psin

#endif // SIMULATOR_TPP
