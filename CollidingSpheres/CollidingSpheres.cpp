// Standard
#include <string>

// ForceModelLib
#include <ForceMethodsDefinitions.h>

// PropertyLib
#include <PropertyDefinitions.h>

// SimulationLib
#include <Simulation.h>

using namespace std;
using namespace PropertyDefinitions;

const string project_root_path = PROJECT_PATH;

int main(int argc, char **argv){
	Simulation simulation; //(project_root_path);

	ForceModel viscoelasticSpheres("ViscoElasticSpheres");
	viscoelasticSpheres.setNormal(normalForceViscoelasticSpheres);
	viscoelasticSpheres.setTangential(tangentialForceHaffWerner);
	viscoelasticSpheres.requireProperty(mass);
	viscoelasticSpheres.requireProperty(moment_of_inertia);
	viscoelasticSpheres.requireProperty(elastic_modulus);
	viscoelasticSpheres.requireProperty(dissipative_constant);
	viscoelasticSpheres.requireProperty(poisson_ratio);
	viscoelasticSpheres.requireProperty(tangential_damping);
	viscoelasticSpheres.requireProperty(friction_parameter);

	simulation.addForceModel(viscoelasticSpheres);


	ForceModel electrostatic("Electrostatic");
	electrostatic.setField(electrostaticForce);
	electrostatic.setNormal(normalForceViscoelasticSpheres);
	electrostatic.setTangential(tangentialForceHaffWerner);
	electrostatic.requireProperty(mass);
	electrostatic.requireProperty(moment_of_inertia);
	electrostatic.requireProperty(elastic_modulus);
	electrostatic.requireProperty(dissipative_constant);
	electrostatic.requireProperty(poisson_ratio);
	electrostatic.requireProperty(tangential_damping);
	electrostatic.requireProperty(friction_parameter);
	electrostatic.requireProperty(electric_charge);

	simulation.addForceModel(electrostatic);

	simulation.setInputFolder(project_root_path + "_input/");
	simulation.setInputFileName("input.txt");
	simulation.readName();

	string simulationName = simulation.getName();

	simulation.setInputMainDataFilePath(project_root_path + "_input/" + simulationName + "/input.txt");
	simulation.setParticleInputFolder(project_root_path + "_input/" + simulationName + "/");
	simulation.setOutputFolder(project_root_path + "_output/" + simulationName + "/");
	simulation.setTimeVectorOutputFileName("timeVector.txt");
	simulation.setTimeVectorForPlotOutputFileName("timeVectorForPlot.txt");

	simulation.inputMainData();

	simulation.initializeParticleArray();

	simulation.outputMainData();

	simulation.simulate();

	simulation.printSuccessMessage();
}
