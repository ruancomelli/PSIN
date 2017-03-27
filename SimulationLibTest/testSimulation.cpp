#define BOOST_TEST_MODULE SimulationLibTest

// UtilsLib
#include <Test.h>

#ifdef BOOST_TEST_MODULE
#	define private public
#endif	// This allows the test to access classes' private members

// SimulationLib
#include <Simulation.h>

// UtilsLib
#include <FileSystem.h>

using namespace std;

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

	pair<string, string> config1 = simulation.getSimulationNameAndRootPath(argc1, argv1);
	pair<string, string> config2 = simulation.getSimulationNameAndRootPath(argc2, argv2);
	pair<string, string> config3 = simulation.getSimulationNameAndRootPath(argc3, argv3);

	checkEqual(config1.first, "Sauron" );
	checkEqual(config2.first, "Simulation1");
	checkEqual(config2.second, "Mordor");
	checkEqual(config3.first, "The Lord of the Rings");
	checkEqual(config3.second, "Mines of Moria");

	checkEqual(config1.first, simulation.getSimulationName(argc1, argv1));
	checkEqual(config2.first, simulation.getSimulationName(argc2, argv2));
	checkEqual(config2.second, simulation.getSimulationRootPath(argc2, argv2));
	checkEqual(config3.first, simulation.getSimulationName(argc3, argv3));
	checkEqual(config3.second, simulation.getSimulationRootPath(argc3, argv3));
}

// For the next test to work, Simulation::checkPathExistance must be declared as public

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
//	check( !Simulation::checkPathExistance(value, destination, name, functionName) );
//	
//	createDirectory(value);
//
//	check(Simulation::checkPathExistance(value, destination, name, functionName));
//
//	checkEqual(value, destination);
//}

TestCase(SimulateTest)
{
	/*TO DO*/
	
	// Probably, we should save a simulation that is known to be correct.
	// This test would only run a simulation and compare the output values.
}