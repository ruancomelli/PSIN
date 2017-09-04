#ifndef SIMULATION_TPP
#define SIMULATION_TPP

// JSONLib
#include <json.hpp>

// SimulationLib
#include <CommandLineParser.hpp>

#include <fstream>

namespace psin {

template<
	typename ... ParticleTypes,
	typename ... InteractionTypes
>
void Simulation<
	ParticleList<ParticleTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
>::setup(int argc, char * argv[])
{
	auto simulationPath = CommandLineParser::parseArgvIntoSimulationPath(argc, argv);

	json j;
	std::ifstream in(simulationPath);
	in >> j;

	this->initialTime = j["initialTime"];
	this->timeStep = j["timeStep"];
	this->finalTime = j["finalTime"];
	this->taylorOrder = j["taylorOrder"];
	this->dimension = j["dimension"];
	this->timeStepsForOutput = j["timeStepsForOutput"];

	json interactions = j["interactions"];
	for(auto& entry : interactions)
	{
		??
	}

	json particles = j["particles"];
	for(auto& entry : particles)
	{
		??
	}
}

} // psin

#endif // SIMULATION_TPP
