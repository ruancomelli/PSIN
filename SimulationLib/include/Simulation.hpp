#ifndef SIMULATION_HPP
#define SIMULATION_HPP

// InteractionLib
#include <Interaction.hpp>

// IOLib
#include <SphericalParticlePtrArrayKit.hpp>

// SimulationLib
#include <LooperDefinitions.hpp>
#include <SeekerDefinitions.hpp>
#include <SimulationFileTree.hpp>

// UtilsLib
#include <Named.hpp>
#include <Vector3D.hpp>

// Standard
#include <string>

namespace psin
{

template<typename ... ParticleTypes> using ParticleList = mp::type_list<ParticleTypes...>;
template<typename ... InteractionTypes> using InteractionList = mp::type_list<InteractionTypes...>;
template<typename ... LooperTypes> using LooperList = mp::type_list<LooperTypes...>;
template<typename ... SeekerTypes> using SeekerList = mp::type_list<SeekerTypes...>;

template<
	typename Particles,
	typename Interactions,
	typename Loopers,
	typename Seekers
> 
class Simulation;

template<
	typename ... ParticleTypes,
	typename ... InteractionTypes
>
class Simulation<
	ParticleList<ParticleTypes...>,
	InteractionList<InteractionTypes...>,
	LooperList<GearLooper>,
	SeekerList<CollisionSeeker>
> : public Named
{
public:
	// using ParticleList = psin::ParticleList<ParticleTypes...>;
	// using InteractionList = psin::InteractionList<InteractionTypes...>;
	// using LooperList = psin::LooperList<GearLooper>;
	// using SeekerList = psin::SeekerList<CollisionSeeker>;

	void setup(int argc, char * argv[]);

	// Default Simulation
	// This function sets paths, inputs and simulates
	void defaultSimulate(const std::string simulationName, const std::string projectRootFolder);

	// Input
	void inputMainData(void);

	// Output
	void outputMainData(void) const;
	void printSuccessMessage(void) const;

	// Particles
	void initializeParticleArray(void);

	// Simulate
	void simulate(void);

private:	
	SimulationFileTree fileTree;

	double initialTime;
	double timeStep;
	double finalTime;
	int taylorOrder;
	int dimension;
	int numberOfParticles;
	int timeStepsForOutput;

	std::tuple< std::vector<ParticleTypes>... > particles;
};

	// public:
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


} // psin

#include <Simulation.tpp>

#endif
