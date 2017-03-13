#include <Simulation.h>

// IOLib
#include <FileReader.h>

void Simulation::inputMainData(void)
{
	FileReader inputData(this->inputFolder + this->simulationName + "/input.txt");

	// Read simulation data
	inputData.readValue("<initialTime>", this->initialTime);
	inputData.readValue("<timeStep>", this->timeStep);
	inputData.readValue("<finalTime>", this->finalTime);
	inputData.readValue("<taylorOrder>", this->taylorOrder);
	inputData.readValue("<dimension>", this->dimension);
	inputData.readValue("<numberOfParticles>", this->numberOfParticles);
	inputData.readValue("<gravity>", this->gravity);
	inputData.readValue("<timeStepsForOutput>", this->timeStepsForOutput);

	// Read ForceModel
	inputData.readValue("<ForceModelName>", forceModelName);

	ForceModel forceModel;

	for (auto& fm : forceModelSet)
	{
		if (fm.getName() == forceModelName)
		{
			forceModel = fm;
			break;
		}
	}
}