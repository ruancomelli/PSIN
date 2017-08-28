#ifndef SIMULATION_FILE_TREE_HPP
#define SIMULATION_FILE_TREE_HPP

// Standard
#include <fstream>
#include <string>


struct SimulationFileTree
{
	using string = std::string;

public:
	// Set simulation name and all other folders
	bool setTree(const string & simulationName, const string & projectRootFolder);

	// Set files
	bool setSimulationName(const string & simulationName);

	bool setProjectRootFolder(const string & projectRootFolder);
	bool setInputFolder(const string & inputFolder);
	bool setInputMainDataFilePath(const string & inputMainDataFilePath);
	bool setParticleInputFolder(const string & particleInputFolder);

	bool setOutputFolder(const string & outputFolder);
	bool setNumericalOutputFolder(const string & numericalOutputFolder);
	bool setGraphicalOutputFolder(const string & graphicalOutputFolder);
	bool setTimeVectorOutputFileName(const string & timeVectorOutputFileName);
	bool setTimeVectorForPlotOutputFileName(const string & timeVectorForPlotOutputFileName);

	// Get files
	string getProjectRootFolder(void) const;
	string getInputFolder(void) const;
	string getInputFileName(void) const;
	string getInputMainDataFilePath(void) const;
	string getParticleInputFolder(void) const;

	string getOutputFolder(void) const;
	string getNumericalOutputFolder(void) const;
	string getGraphicalOutputFolder(void) const;
	string getTimeVectorOutputFileName(void) const;
	string getTimeVectorForPlotOutputFileName(void) const;
	
	std::ofstream timeVectorFile;
	std::ofstream timeVectorForPlotFile;

private:
	// ---- Simulation Folders and Paths ----
	string simulationName;

	// input
	string projectRootFolder;	// This should be something like C:/ParticleSimulator/
	string inputFolder;	// This should be something like project_root_path + "_input/"
	string particleInputFolder;	// This should be something like inputFolder + simulation.getName() + "/"
	string inputMainDataFilePath; // This should be something like inputFolder + "Simulation1/" + "input.txt"
	// output
	string outputFolder;	// This should be something like project_root_path + "_output/"
	string numericalOutputFolder;	// This should be something like outputFolder + simulation.getName() + "/Numerical/"
	string graphicalOutputFolder;	// This should be something like outputFolder + simulation.getName() + "/Graphical/"
	string timeVectorOutputFileName; // This should be something like project_root_path + "_output/" + simulation.getName() + "/timeVector.txt"
	string timeVectorForPlotOutputFileName; // This should be something like project_root_path + "_output/" + simulation.getName() + "/timeVectorForPlot.txt"

	// Auxiliary function
	static bool setPathIfPathExists(const string & value, string & destination, const string & name, const string & functionName );

}; // class SimulationFileTree


#endif	// SIMULATION_FILE_TREE_HPP
