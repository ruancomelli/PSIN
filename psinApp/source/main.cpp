// UtilsLib
#include <FileSystem.hpp>
#include <string.hpp>

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

using namespace psin;

int main(int argc, char* argv[])
{
	path projectRootPath = filesystem::current_path().parent_path().parent_path().parent_path();	

	path simulatorRootPath = projectRootPath / "psinApp";
	path mainInputFilePath = simulatorRootPath / "SimulationInputFiles" / "main.json";

	program_options::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("path", program_options::value<string>(), "Project's root folder")
	;
	program_options::variables_map vm = psin::parseCommandLine(
			argc, 
			argv, 
			desc
		);
	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
	}
	if(vm.count("path"))
	{
		mainInputFilePath = path(vm["path"].as<string>());
	}

	using ParticleList = psin::ParticleList<
		SphericalParticle<
			Mass,
			Volume,
			MomentOfInertia,
			DissipativeConstant,
			PoissonRatio,
			ElasticModulus,
			TangentialDamping,
			FrictionParameter,
			ElectricCharge,
			NormalDissipativeConstant,
			Color
			>
		>;

	using BoundaryList = psin::BoundaryList<
		FixedInfinitePlane<
			ElasticModulus,
			NormalDissipativeConstant,
			Color
			>,
		GravityField,
		SurroundingFluid<SpecificMass>
		>;
		
	using InteractionList = psin::InteractionList<
		ElectrostaticForce,
		NormalForceLinearDashpotForce,
		NormalForceViscoelasticSpheres,
		GravityForce,
		TangentialForceCundallStrack,
		TangentialForceHaffWerner,
		DragForce
		>;
		
	using LooperList = psin::LooperList<GearLooper>;

	using SeekerList = psin::SeekerList<BlindSeeker>;
	
	Simulation<
		ParticleList,
		BoundaryList,
		InteractionList,
		LooperList,
		SeekerList
	> simulation;

	std::cout << "\nmainInputFilePath: " << mainInputFilePath.string() << std::endl; // DEBUG

	simulation.setup( mainInputFilePath );
	simulation.outputMainData();
	simulation.backupInteractions();
	simulation.backupParticles();
	simulation.backupBoundaries();
	simulation.simulate();
}