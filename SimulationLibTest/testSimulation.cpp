#define BOOST_TEST_MODULE SimulationLibTest

// UtilsLib
#include <FileSystem.hpp>
#include <Test.hpp>

// SimulationLib
#include <InteractionSubjectLister.hpp>
#include <Simulation.hpp>

// Standard
#include <type_traits>

using namespace std;

namespace InteractionSubjectLister_Test_namespace {
	struct A
	{};

	struct B
	{};
	
	struct C
	{};

	struct I
	{
		template<typename T, typename U>
		struct check : bool_type< (is_same<T, A>::value || is_same<T, B>::value) && (is_same<U, A>::value || is_same<U, B>::value) >
		{};
	};

	struct J
	{
		template<typename T, typename U>
		struct check : bool_type< is_same<T, C>::value && is_same<U, B>::value >
		{};
	};
} // InteractionSubjectLister_Test_namespace

TestCase(InteractionSubjectLister_Test)
{
	using namespace InteractionSubjectLister_Test_namespace;

	check((
		std::is_same<
			traits::generate_triplets< type_list<I, J>, type_list<A, B, C> >::type,
			type_list<
				type_list<I, A, A>,
				type_list<J, A, A>,
				type_list<I, B, A>,
				type_list<J, B, A>,
				type_list<I, C, A>,
				type_list<J, C, A>,

				type_list<I, A, B>,
				type_list<J, A, B>,
				type_list<I, B, B>,
				type_list<J, B, B>,
				type_list<I, C, B>,
				type_list<J, C, B>,

				type_list<I, A, C>,
				type_list<J, A, C>,
				type_list<I, B, C>,
				type_list<J, B, C>,
				type_list<I, C, C>,
				type_list<J, C, C>
			>
		>::value
	));

	check((
		std::is_same<
			traits::get_valid_triplets< traits::generate_triplets< type_list<I, J>, type_list<A, B, C> >::type >::type,
			type_list<
				type_list<I, A, A>,
				type_list<I, B, A>,

				type_list<I, A, B>,
				type_list<I, B, B>,
				type_list<J, C, B>
			>
		>::value
	));

	check((
		std::is_same<
			InteractionSubjectLister::generate_combinations< type_list<I, J>, type_list<A, B, C> >::type,
			type_list<
				type_list<I, A, A>,
				type_list<I, B, A>,

				type_list<I, A, B>,
				type_list<I, B, B>,
				type_list<J, C, B>
			>
		>::value
	));
}

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

// TestCase(SimulationFileTreeTest)
// {
// 	SimulationFileTree fileTree;

// 	string currentDir = ::currentDirectory();
// 	string simulationName = "RohanSimulation";

// 	string rootFolder = currentDir + "/root/";
// 	::createDirectory(rootFolder);
// 	check(fileTree.setProjectRootFolder(rootFolder));
// 	checkEqual(fileTree.getProjectRootFolder(), rootFolder);

// 	string inputFolder = rootFolder + "_input/";
// 	::createDirectory(inputFolder);
// 	check(fileTree.setInputFolder(inputFolder));
// 	checkEqual(fileTree.getInputFolder(), inputFolder);

// 	string particleInputFolder = inputFolder + simulationName + "/";
// 	::createDirectory(particleInputFolder);
// 	check(fileTree.setParticleInputFolder(particleInputFolder));
// 	checkEqual(fileTree.getParticleInputFolder(), particleInputFolder);

// 	string inputMainDataFilePath = particleInputFolder + "mainInfoInput.txt";
// 	::deletePath(inputMainDataFilePath);
// 	ofstream of1(inputMainDataFilePath);
// 	check(fileTree.setInputMainDataFilePath(inputMainDataFilePath));
// 	checkEqual(fileTree.getInputMainDataFilePath(), inputMainDataFilePath);

// 	string outputFolder = rootFolder + "_output/" + simulationName + "/";
// 	check(fileTree.setOutputFolder(outputFolder));
// 	checkEqual(fileTree.getOutputFolder(), outputFolder);

// 	string numericalOutputFolder = rootFolder + "_output/" + simulationName + "/Numerical/";
// 	check(fileTree.setNumericalOutputFolder(numericalOutputFolder));
// 	checkEqual(fileTree.getNumericalOutputFolder(), numericalOutputFolder);

// 	string graphicalOutputFolder = rootFolder + "_output/" + simulationName + "/Graphical/";
// 	check(fileTree.setGraphicalOutputFolder(graphicalOutputFolder));
// 	checkEqual(fileTree.getGraphicalOutputFolder(), graphicalOutputFolder);

// 	string timeVectorFileName = "timeVector.txt";
// 	check(fileTree.setTimeVectorOutputFileName(timeVectorFileName));

// 	string timeVectorForPlotOutputFileName = "timeVectorForPlot.txt";
// 	check(fileTree.setTimeVectorForPlotOutputFileName(timeVectorForPlotOutputFileName));
// }

// TestCase(GetSimulationNameAndRootPathTest)
// {
// 	Simulation simulation;

// 	char * argv1[] = { "myProgramName", "--simulation=Sauron" }; // ./myProgramName --simulation=Sauron
// 	char * argv2[] = { "myProgramName", "--root=Mordor" }; // ./myProgramName --root=Mordor
// 	char * argv3[] = { "myProgramName", "--simulation=The Lord of the Rings", "--root=Mines of Moria" };
// 		// ./myProgramName --simulation="The Lord of the Rings" --root="Mines of Moria"

// 	int argc1 = 2;
// 	int argc2 = 2;
// 	int argc3 = 3;

// 	pair<string, string> config1 = simulation.parseArgvIntoSimulationNameAndRootPath(argc1, argv1);
// 	pair<string, string> config2 = simulation.parseArgvIntoSimulationNameAndRootPath(argc2, argv2);
// 	pair<string, string> config3 = simulation.parseArgvIntoSimulationNameAndRootPath(argc3, argv3);

// 	checkEqual(config1.first, "Sauron" );
// 	checkEqual(config2.first, "Simulation1");
// 	checkEqual(config2.second, "Mordor");
// 	checkEqual(config3.first, "The Lord of the Rings");
// 	checkEqual(config3.second, "Mines of Moria");

// 	checkEqual(config1.first, simulation.parseArgvIntoSimulationName(argc1, argv1));
// 	checkEqual(config2.first, simulation.parseArgvIntoSimulationName(argc2, argv2));
// 	checkEqual(config2.second, simulation.parseArgvIntoSimulationRootPath(argc2, argv2));
// 	checkEqual(config3.first, simulation.parseArgvIntoSimulationName(argc3, argv3));
// 	checkEqual(config3.second, simulation.parseArgvIntoSimulationRootPath(argc3, argv3));
// }

// TestCase(SimulateTest)
// {
// 	/*TO DO*/
	
// 	// Probably, we should save a simulation that is known to be correct.
// 	// This test would only run a simulation and compare the output values.
// }