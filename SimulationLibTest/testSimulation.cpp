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

	string current = currentDirectory();

	char * argv1[] = { "--simulation=Sauron" };
	char * argv2[] = { "--root=Mordor" };
	char * argv3[] = { "--simulation=Sauron", "--root=Mordor" };

	int argc1 = 1;
	int argc2 = 1;
	int argc3 = 2;

	pair<string, string> config1 = simulation.getSimulationNameAndRootPath(argc1, argv1);
	pair<string, string> config2 = simulation.getSimulationNameAndRootPath(argc2, argv2);
	pair<string, string> config3 = simulation.getSimulationNameAndRootPath(argc3, argv3);

	checkEqual(config1.first, "Sauron" );
	checkEqual(config1.second, current);
	checkEqual(config2.first, "Simulation1");
	checkEqual(config2.second, "Mordor");
	checkEqual(config3.first, "Sauron");
	checkEqual(config3.second, "Mordor");
}