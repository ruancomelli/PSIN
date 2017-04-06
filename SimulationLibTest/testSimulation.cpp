#define BOOST_TEST_MODULE SimulationLibTest

// UtilsLib
#include <Test.hpp>

#ifdef BOOST_TEST_MODULE
#	define private public
#endif	// This allows the test to access classes' private members

// SimulationLib
#include <Simulation.hpp>

// UtilsLib
#include <FileSystem.hpp>

using namespace std;

// For the next test to work, SimulationFileTree::setPathIfPathExists must be declared as public

//TestCase(CheckPathExistanceTest)
//{
//	string current = currentDirectory();
//
//	string value = current + "Steve/";
//	string destination = "empty";
//	string name = "Folder";
//	string functionName = "Test Function";
//
//	deletePath(current + "Steve/");
//
//	check( !SimulationFileTree::setPathIfPathExists(value, destination, name, functionName) );
//	
//	createDirectory(value);
//
//	check(SimulationFileTree::setPathIfPathExists(value, destination, name, functionName));
//
//	checkEqual(value, destination);
//}

TestCase(SimulationFileTreeTest)
{
	SimulationFileTree fileTree;

	string currentDir = ::currentDirectory();
	string simulationName = "RohanSimulation";

	string rootFolder = currentDir + "/root/";
	::createDirectory(rootFolder);
	check(fileTree.setProjectRootFolder(rootFolder));
	checkEqual(fileTree.getProjectRootFolder(), rootFolder);

	string inputFolder = rootFolder + "_input/";
	::createDirectory(inputFolder);
	check(fileTree.setInputFolder(inputFolder));
	checkEqual(fileTree.getInputFolder(), inputFolder);

	string particleInputFolder = inputFolder + simulationName + "/";
	::createDirectory(particleInputFolder);
	check(fileTree.setParticleInputFolder(particleInputFolder));
	checkEqual(fileTree.getParticleInputFolder(), particleInputFolder);

	string inputMainDataFilePath = particleInputFolder + "mainInfoInput.txt";
	::deletePath(inputMainDataFilePath);
	ofstream of1(inputMainDataFilePath);
	check(fileTree.setInputMainDataFilePath(inputMainDataFilePath));
	checkEqual(fileTree.getInputMainDataFilePath(), inputMainDataFilePath);

	string outputFolder = rootFolder + "_output/" + simulationName + "/";
	check(fileTree.setOutputFolder(outputFolder));
	checkEqual(fileTree.getOutputFolder(), outputFolder);

	string numericalOutputFolder = rootFolder + "_output/" + simulationName + "/Numerical/";
	check(fileTree.setNumericalOutputFolder(numericalOutputFolder));
	checkEqual(fileTree.getNumericalOutputFolder(), numericalOutputFolder);

	string graphicalOutputFolder = rootFolder + "_output/" + simulationName + "/Graphical/";
	check(fileTree.setGraphicalOutputFolder(graphicalOutputFolder));
	checkEqual(fileTree.getGraphicalOutputFolder(), graphicalOutputFolder);

	string timeVectorFileName = "timeVector.txt";
	check(fileTree.setTimeVectorOutputFileName(timeVectorFileName));

	string timeVectorForPlotOutputFileName = "timeVectorForPlot.txt";
	check(fileTree.setTimeVectorForPlotOutputFileName(timeVectorForPlotOutputFileName));
}

TestCase(GetSimulationNameAndRootPathTest)
{
	Simulation simulation;

	char * argv1[] = { "myProgramName", "--simulation=Sauron" }; // ./myProgramName --simulation=Sauron
	char * argv2[] = { "myProgramName", "--root=Mordor" }; // ./myProgramName --root=Mordor
	char * argv3[] = { "myProgramName", "--simulation=The Lord of the Rings", "--root=Mines of Moria" };
		// ./myProgramName --simulation="The Lord of the Rings" --root="Mines of Moria"

	int argc1 = 2;
	int argc2 = 2;
	int argc3 = 3;

	pair<string, string> config1 = simulation.parseArgvIntoSimulationNameAndRootPath(argc1, argv1);
	pair<string, string> config2 = simulation.parseArgvIntoSimulationNameAndRootPath(argc2, argv2);
	pair<string, string> config3 = simulation.parseArgvIntoSimulationNameAndRootPath(argc3, argv3);

	checkEqual(config1.first, "Sauron" );
	checkEqual(config2.first, "Simulation1");
	checkEqual(config2.second, "Mordor");
	checkEqual(config3.first, "The Lord of the Rings");
	checkEqual(config3.second, "Mines of Moria");

	checkEqual(config1.first, simulation.parseArgvIntoSimulationName(argc1, argv1));
	checkEqual(config2.first, simulation.parseArgvIntoSimulationName(argc2, argv2));
	checkEqual(config2.second, simulation.parseArgvIntoSimulationRootPath(argc2, argv2));
	checkEqual(config3.first, simulation.parseArgvIntoSimulationName(argc3, argv3));
	checkEqual(config3.second, simulation.parseArgvIntoSimulationRootPath(argc3, argv3));
}

TestCase(SimulateTest)
{
	/*TO DO*/
	
	// Probably, we should save a simulation that is known to be correct.
	// This test would only run a simulation and compare the output values.
}