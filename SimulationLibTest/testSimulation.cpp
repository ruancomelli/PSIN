#define BOOST_TEST_MODULE SimulationLibTest

// UtilsLib
#include <FileSystem.hpp>
#include <string.hpp>
#include <Test.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

// EntityLib
#include <FixedInfinitePlane.hpp>
#include <GravityField.hpp>
#include <SphericalParticle.hpp>

// InteractionLib
#include <InteractionDefinitions.hpp>

// SimulationLib
#include <CommandLineParser.hpp>
#include <InteractionSubjectLister.hpp>
#include <ProgramOptions.hpp>
#include <Simulation.hpp>

// Standard
#include <type_traits>

using namespace std;
using namespace psin;

namespace InteractionSubjectLister_Test_namespace {
	struct A
	{};

	struct B
	{};
	
	struct C
	{};

	struct D
	{};

	struct I
	{
		template<typename T, typename U>
		struct check : mp::bool_constant< (is_same<T, A>::value or is_same<T, B>::value) and (is_same<U, A>::value or is_same<U, B>::value) >
		{};
	};

	struct J
	{
		template<typename T, typename U>
		struct check : mp::bool_constant< is_same<T, C>::value and is_same<U, B>::value >
		{};
	};
} // InteractionSubjectLister_Test_namespace

TestCase(InteractionSubjectLister_Test)
{
	using namespace InteractionSubjectLister_Test_namespace;

	check((
		std::is_same<
			detail::generate_triplets< mp::type_list<I, J>, mp::type_list<A, B, C>, mp::type_list<A, B, C> >::type,
			mp::type_list<
				mp::type_list<I, A, A>,
				mp::type_list<J, A, A>,
				mp::type_list<I, B, A>,
				mp::type_list<J, B, A>,
				mp::type_list<I, C, A>,
				mp::type_list<J, C, A>,

				mp::type_list<I, A, B>,
				mp::type_list<J, A, B>,
				mp::type_list<I, B, B>,
				mp::type_list<J, B, B>,
				mp::type_list<I, C, B>,
				mp::type_list<J, C, B>,

				mp::type_list<I, A, C>,
				mp::type_list<J, A, C>,
				mp::type_list<I, B, C>,
				mp::type_list<J, B, C>,
				mp::type_list<I, C, C>,
				mp::type_list<J, C, C>
			>
		>::value
	));

	check((
		std::is_same<
			detail::get_valid_triplets< detail::generate_triplets< mp::type_list<I, J>, mp::type_list<A, B, C> >::type >::type,
			mp::type_list<
				mp::type_list<I, A, A>,
				mp::type_list<I, B, A>,

				mp::type_list<I, A, B>,
				mp::type_list<I, B, B>,
				mp::type_list<J, C, B>
			>
		>::value
	));

	check((
		std::is_same<
			InteractionSubjectLister::generate_combinations< mp::type_list<I, J>, mp::type_list<A, B, C, D> >::type,
			mp::type_list<
				mp::type_list<I, A, A>,
				mp::type_list<I, B, A>,

				mp::type_list<I, B, B>,
				mp::type_list<J, C, B>
			>
		>::value
	));
}

TestCase(Simulation_Instantiation_Test)
{
	Simulation<
		ParticleList<
			SphericalParticle<
				Mass,
				Volume,
				MomentOfInertia,
				PoissonRatio
				>
			>,
		BoundaryList<>,
		InteractionList<
			ElectrostaticForce,
			NormalForceLinearDashpotForce,
			NormalForceHertz,
			TangentialForceCundallStrack,
			TangentialForceHaffWerner
			>,
		LooperList<GearLooper>,
		SeekerList<CollisionSeeker>
	> simulation;
}

TestCase(Simulation_setup_Test)
{
	path projectRootPath = filesystem::current_path().parent_path().parent_path().parent_path();	
	program_options::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("path", program_options::value<string>(), "Project's root folder")
	;
	program_options::variables_map vm = psin::parseCommandLine(
			boost::unit_test::framework::master_test_suite().argc, 
			boost::unit_test::framework::master_test_suite().argv, 
			desc
		);
	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
	}
	if(vm.count("path"))
	{
		projectRootPath = path(vm["path"].as<string>());
	}

	Simulation<
		ParticleList<
			SphericalParticle<
				Mass,
				Volume,
				MomentOfInertia,
				PoissonRatio
				>
			>,
		BoundaryList<>,
		InteractionList<
			ElectrostaticForce,
			NormalForceLinearDashpotForce,
			NormalForceHertz,
			TangentialForceCundallStrack,
			TangentialForceHaffWerner
			>,
		LooperList<GearLooper>,
		SeekerList<CollisionSeeker>
	> simulation;

	path simulationLibTestPath = projectRootPath / "SimulationLibTest";
	path mainInputFilePath = simulationLibTestPath / "SimulationInputFiles" / "main.json";
	simulation.setup( mainInputFilePath );
}

TestCase(Simulation_setup_and_outputMainData_Test)
{
	path projectRootPath = filesystem::current_path().parent_path().parent_path().parent_path();	
	program_options::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("path", program_options::value<string>(), "Project's root folder")
	;
	program_options::variables_map vm = psin::parseCommandLine(
			boost::unit_test::framework::master_test_suite().argc, 
			boost::unit_test::framework::master_test_suite().argv, 
			desc
		);
	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
	}
	if(vm.count("path"))
	{
		projectRootPath = path(vm["path"].as<string>());
	}

	Simulation<
		ParticleList<
			SphericalParticle<
				Mass,
				Volume,
				MomentOfInertia,
				PoissonRatio
				>
			>,
		BoundaryList<>,
		InteractionList<
			ElectrostaticForce,
			NormalForceLinearDashpotForce,
			NormalForceHertz,
			TangentialForceCundallStrack,
			TangentialForceHaffWerner
			>,
		LooperList<GearLooper>,
		SeekerList<CollisionSeeker>
	> simulation;

	path simulationLibTestPath = projectRootPath / "SimulationLibTest";
	path mainInputFilePath = simulationLibTestPath / "SimulationInputFiles" / "main.json";

	simulation.setup( mainInputFilePath );
	simulation.outputMainData();
	simulation.backupInteractions();
	simulation.backupParticles();
	simulation.backupBoundaries();
}

TestCase(Simulation_simulate_Test)
{
	path projectRootPath = filesystem::current_path().parent_path().parent_path().parent_path();	
	program_options::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("path", program_options::value<string>(), "Project's root folder")
	;
	program_options::variables_map vm = psin::parseCommandLine(
			boost::unit_test::framework::master_test_suite().argc, 
			boost::unit_test::framework::master_test_suite().argv, 
			desc
		);
	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
	}
	if(vm.count("path"))
	{
		projectRootPath = path(vm["path"].as<string>());
	}
	
	Simulation<
		ParticleList<
			SphericalParticle<
				Mass,
				Volume,
				MomentOfInertia,
				PoissonRatio
				>
			>,
		BoundaryList<>,
		InteractionList<
			ElectrostaticForce,
			NormalForceLinearDashpotForce,
			NormalForceHertz,
			TangentialForceCundallStrack,
			TangentialForceHaffWerner
			>,
		LooperList<GearLooper>,
		SeekerList<CollisionSeeker>
	> simulation;

	path simulationLibTestPath = projectRootPath / "SimulationLibTest";
	path mainInputFilePath = simulationLibTestPath / "SimulationInputFiles" / "main.json";
	simulation.setup( mainInputFilePath );
	simulation.outputMainData();
	simulation.backupInteractions();
	simulation.backupParticles();
	simulation.backupBoundaries();
	simulation.simulate();
}

TestCase(Simulation_simulate_with_boundary_Test)
{
	path projectRootPath = filesystem::current_path().parent_path().parent_path().parent_path();	
	program_options::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("path", program_options::value<string>(), "Project's root folder")
	;
	program_options::variables_map vm = psin::parseCommandLine(
			boost::unit_test::framework::master_test_suite().argc, 
			boost::unit_test::framework::master_test_suite().argv, 
			desc
		);
	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
	}
	if(vm.count("path"))
	{
		projectRootPath = path(vm["path"].as<string>());
	}
	
	Simulation<
		ParticleList<
			SphericalParticle<
				Mass,
				Volume,
				MomentOfInertia,
				PoissonRatio
				>
			>,
		BoundaryList<
			FixedInfinitePlane<
				
				>,
			GravityField
			>,
		InteractionList<
			ElectrostaticForce,
			NormalForceLinearDashpotForce,
			NormalForceHertz,
			TangentialForceCundallStrack,
			TangentialForceHaffWerner
			>,
		LooperList<GearLooper>,
		SeekerList<CollisionSeeker>
	> simulation;

	path simulationLibTestPath = projectRootPath / "SimulationLibTest";
	path mainInputFilePath = simulationLibTestPath / "SimulationInputFiles" / "main.json";
	simulation.setup( mainInputFilePath );
	simulation.outputMainData();
	simulation.backupInteractions();
	simulation.backupParticles();
	simulation.backupBoundaries();
	simulation.simulate();
}

TestCase(SimulationFileTreeTest)
{
	SimulationFileTree fileTree;

	string currentDir = psin::currentDirectory();
	string simulationName = "RohanSimulation";

	string rootFolder = currentDir + "/root/";
	psin::createDirectory(rootFolder);
	check(fileTree.setProjectRootFolder(rootFolder));
	checkEqual(fileTree.getProjectRootFolder(), rootFolder);

	string inputFolder = rootFolder + "_input/";
	psin::createDirectory(inputFolder);
	check(fileTree.setInputFolder(inputFolder));
	checkEqual(fileTree.getInputFolder(), inputFolder);

	string particleInputFolder = inputFolder + simulationName + "/";
	psin::createDirectory(particleInputFolder);
	check(fileTree.setParticleInputFolder(particleInputFolder));
	checkEqual(fileTree.getParticleInputFolder(), particleInputFolder);

	string inputMainDataFilePath = particleInputFolder + "mainInfoInput.txt";
	psin::deletePath(inputMainDataFilePath);
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

TestCase(CommandLineParser_Test)
{
	char * argv1[] = { (char*) "myProgramName", (char*) "--simulation=Sauron" }; // ./myProgramName --simulation=Sauron
	char * argv2[] = { (char*) "myProgramName", (char*) "--root=Mordor" }; // ./myProgramName --root=Mordor
	char * argv3[] = { (char*) "myProgramName", (char*) "--simulation=The Lord of the Rings", (char*) "--root=Mines of Moria" };
		// ./myProgramName --simulation="The Lord of the Rings" --root="Mines of Moria"
	char * argv4[] = { (char*) "myProgramName", (char*) "--path=they/are.here" }; // ./myProgramName --path="they/are.here"

	int argc1 = 2;
	int argc2 = 2;
	int argc3 = 3;
	int argc4 = 2;

	pair<string, string> config1 = CommandLineParser::parseArgvIntoSimulationNameAndRootPath(argc1, argv1);
	pair<string, string> config2 = CommandLineParser::parseArgvIntoSimulationNameAndRootPath(argc2, argv2);
	pair<string, string> config3 = CommandLineParser::parseArgvIntoSimulationNameAndRootPath(argc3, argv3);
	string config4 = CommandLineParser::parseArgvIntoSimulationPath(argc4, argv4);

	checkEqual(config1.first, "Sauron" );
	checkEqual(config2.first, "Simulation1");
	checkEqual(config2.second, "Mordor");
	checkEqual(config3.first, "The Lord of the Rings");
	checkEqual(config3.second, "Mines of Moria");
	checkEqual(config4, "they/are.here");

	checkEqual(config1.first, CommandLineParser::parseArgvIntoSimulationName(argc1, argv1));
	checkEqual(config2.first, CommandLineParser::parseArgvIntoSimulationName(argc2, argv2));
	checkEqual(config2.second, CommandLineParser::parseArgvIntoSimulationRootPath(argc2, argv2));
	checkEqual(config3.first, CommandLineParser::parseArgvIntoSimulationName(argc3, argv3));
	checkEqual(config3.second, CommandLineParser::parseArgvIntoSimulationRootPath(argc3, argv3));
}

// TestCase(SimulateTest)
// {
// 	/*TO DO*/
	
// 	// Probably, we should save a simulation that is known to be correct.
// 	// This test would only run a simulation and compare the output values.
// }