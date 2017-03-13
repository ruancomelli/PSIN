#include <Simulation.h>

// ForceModelLib
#include <ForceModelSet.h>

// IOLib
#include <FileReader.h>

// UtilsLib
#include <Debug.h>
#include <FileSystem.h>

Simulation::Simulation(const string inputFolder)
{
	if( checkPathExists(inputFolder) )
	{
		this->inputFolder = inputFolder;

		FileReader simulationFileReader(inputFolder + "input.txt");
		string simulationName;
		if( simulationFileReader.readValue("<simulationName>", simulationName) )
		{
			this->setName(simulationName);
		}
		else
		{
			this->setName("");
		}
	} 
	else
	{
		cerr << string("Error in ") + string(__CURRENT_FUNCTION__) << endl
			<< "Input Folder named \"" << inputFolder << "\" does not exist" << endl;
	}
}

// Set and get name
void Simulation::setName(const string name)
{
	if(!name.empty()) this->name = name;
	else this->name = "Nameless";
}

string Simulation::getName(void) const
{
	return this->name;
}

void Simulation::inputMainData(void)
{
	FileReader inputData(this->inputFolder + this->getName() + "/input.txt");

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
	string forceModelName;
	inputData.readValue("<ForceModelName>", forceModelName);

	for (auto& fm : forceModelSet)
	{
		if (fm.getName() == forceModelName)
		{
			this->forceModel = fm;
			break;
		}
	}
}