#ifndef SIMULATION_H
#define SIMULATION_H

// ForceModelLib
#include <ForceModel.h>

// IOLib
#include <SphericalParticlePtrArrayKit.h>

// PropertyLib
#include <PropertyDefinitions.h>

// UtilsLib
#include <Vector3D.h>

// Standard
#include <fstream>
#include <string>


class Simulation
{
	using string = std::string;

	public:
		struct ForceModelCompare{
			bool operator()( const ForceModel & left, const ForceModel & right ) const
			{ return left.getName() < right.getName();}
		};

		static std::pair<std::string, std::string> getSimulationNameAndRootPath(int argc, char **argv);
		static std::string getSimulationName(int argc, char **argv);
		static std::string getSimulationRootPath(int argc, char **argv);

		// Default Simulation
		// This function sets paths, inputs and simulates
		void defaultSimulate(const std::string simulationName, const std::string projectRootFolder);

		// Set files
		bool setProjectRootFolder(const string projectRootFolder);
		bool setInputFolder(const string inputFolder);
		bool setInputFileName(const string inputFileName);
		bool setInputMainDataFilePath(const string inputMainDataFilePath);
		bool setParticleInputFolder(const string particleInputFolder);

		bool setOutputFolder(const string outputFolder);
		bool setTimeVectorOutputFileName(const string timeVectorOutputFileName);
		bool setTimeVectorForPlotOutputFileName(const string timeVectorForPlotOutputFileName);

		// Name
		void setName( const string name );
		string getName(void) const;

		// Input
		void readName(void);
		void inputMainData(void);

		// Output
		void outputMainData(void);
		void printSuccessMessage(void);

		// ForceModel
		void addForceModel( const ForceModel & fm );

		// Particles
		void initializeParticleArray(void);

		// Simulate
		void simulate(void);

	private:
		// Simulation Folders and Paths
		string name;	// This should be something like "Simulation1", or "MySimulation"

		// input
		string projectRootFolder;	// This should be something like C:/ParticleSimulator/
		string inputFolder;	// This should be something like project_root_path + "_input/"
		string inputFileName;	// This should be something like "input.txt" (to get the simulation's name)
		string particleInputFolder;	// This should be something like inputFolder + simulationName + "/"
		string inputMainDataFilePath; // This should be something like inputFolder + "Simulation1/" + "input.txt"
		// output
		string outputFolder;	// This should be something like project_root_path + "_output/"
		string timeVectorOutputFileName; // This should be something like project_root_path + "_output/" + simulation.getName() + "/timeVector.txt"
		string timeVectorForPlotOutputFileName; // This should be something like project_root_path + "_output/" + simulation.getName() + "/timeVectorForPlot.txt"

		// Files
		std::ofstream timeVectorFile;
		std::ofstream timeVectorForPlotFile;

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
		ForceModel forceModel;
		std::set<ForceModel, Simulation::ForceModelCompare> forceModelSet;

}; // class Simulation


#endif	// SIMULATION_H


