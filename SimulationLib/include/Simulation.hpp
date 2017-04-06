#ifndef SIMULATION_H
#define SIMULATION_H

// ForceModelLib
#include <ForceModel.hpp>

// IOLib
#include <SphericalParticlePtrArrayKit.hpp>

// SimulationLib
#include <SimulationFileTree.hpp>

// UtilsLib
#include <Named.hpp>
#include <Vector3D.hpp>

// Standard
#include <string>


class Simulation : public Named
{
	public:
		static std::pair<std::string, std::string> parseArgvIntoSimulationNameAndRootPath(int argc, char **argv);
		static std::string parseArgvIntoSimulationName(int argc, char **argv);
		static std::string parseArgvIntoSimulationRootPath(int argc, char **argv);

		// Default Simulation
		// This function sets paths, inputs and simulates
		void defaultSimulate(const std::string simulationName, const std::string projectRootFolder);

		// Input
		void inputMainData(void);

		// Output
		void outputMainData(void) const;
		void printSuccessMessage(void) const;

		// ForceModel
		void appendForceModel( const ForceModel<SphericalParticle, SphericalParticle> & fm );

		// Particles
		void initializeParticleArray(void);

		// Simulate
		void simulate(void);

	private:

		// Files
		SimulationFileTree fileTree;

		// Simulation data
		double initialTime;
		double timeStep;
		double finalTime;
		int taylorOrder;
		int dimension;
		int numberOfParticles;
		int timeStepsForOutput;
		Vector3D gravity = Vector3D();

		// Simulation objects
		SphericalParticlePtrArrayKit particleArray;
		ForceModel<SphericalParticle, SphericalParticle> forceModel;
		std::set<ForceModel<SphericalParticle, SphericalParticle>, Named::NamedCompare> forceModelSet;

}; // class Simulation


#endif	// SIMULATION_H
