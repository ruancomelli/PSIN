#ifndef SIMULATION_HPP
#define SIMULATION_HPP

// InteractionLib
#include <Interaction.hpp>

// IOLib
#include <SphericalParticlePtrArrayKit.hpp>

// SimulationLib
#include <SimulationFileTree.hpp>

// UtilsLib
#include <Named.hpp>
#include <Vector3D.hpp>

// Standard
#include <string>

template<typename ... PropertyTypes> using PropertyList = type_list<PropertyTypes...>;
template<typename ... ParticleTypes> using ParticleList = type_list<ParticleTypes...>;
template<typename ... InteractionTypes> using InteractionList = type_list<InteractionTypes...>;
template<typename ... LooperTypes> using LooperList = type_list<LooperTypes...>;
template<typename ... SeekerTypes> using SeekerList = type_list<SeekerTypes...>;

template<
	typename Properties,
	typename Particles,
	typename Interactions,
	typename Loopers,
	typename SeekerList
> 
class Simulation;

template<
	typename ... PropertyTypes,
	typename ... ParticleTypes,
	typename ... InteractionTypes,
	typename ... LooperTypes,
	typename ... SeekerTypes
>
class Simulation<
	PropertyList<PropertyTypes...>,
	ParticleList<ParticleTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<LooperTypes...>,
	SeekerList<SeekerTypes...>
> : public Named
{
	// public:
	// 	static std::pair<std::string, std::string> parseArgvIntoSimulationNameAndRootPath(int argc, char **argv);
	// 	static std::string parseArgvIntoSimulationName(int argc, char **argv);
	// 	static std::string parseArgvIntoSimulationRootPath(int argc, char **argv);

	// 	// Default Simulation
	// 	// This function sets paths, inputs and simulates
	// 	void defaultSimulate(const std::string simulationName, const std::string projectRootFolder);

	// 	// Input
	// 	void inputMainData(void);

	// 	// Output
	// 	void outputMainData(void) const;
	// 	void printSuccessMessage(void) const;

	// 	// Interaction
	// 	void setInteraction(const std::string & InteractionName);
	// 	void appendInteraction(const Interaction<SphericalParticle, SphericalParticle> & fm);

	// 	// Particles
	// 	void initializeParticleArray(void);

	// 	// Simulate
	// 	void simulate(void);

	// private:
	// 	// Files
	// 	SimulationFileTree fileTree;

	// 	// Simulation data
	// 	double initialTime;
	// 	double timeStep;
	// 	double finalTime;
	// 	int taylorOrder;
	// 	int dimension;
	// 	int numberOfParticles;
	// 	int timeStepsForOutput;
	// 	Vector3D gravity = Vector3D();

	// 	// Simulation objects
	// 	SphericalParticlePtrArrayKit particleArray;
	// 	Interaction<SphericalParticle, SphericalParticle> Interaction;
	// 	std::set<Interaction<SphericalParticle, SphericalParticle>, Named::NamedCompare> InteractionSet;

};


#endif
