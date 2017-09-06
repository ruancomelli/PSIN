#include <Simulation.hpp>

// UtilsLib
#include <Debug.hpp>
#include <FileSystem.hpp>

namespace psin {

bool SimulationFileTree::setTree(const std::string & simulationName, const std::string & projectRootFolder)
{
	bool boolFlag = true;

	this->simulationName = simulationName;

	boolFlag = boolFlag and this->setProjectRootFolder(projectRootFolder);
	boolFlag = boolFlag and this->setInputFolder(projectRootFolder + "_input/");

	boolFlag = boolFlag and this->setInputMainDataFilePath(projectRootFolder + "_input/" + simulationName + "/mainInfoInput.txt");
	boolFlag = boolFlag and this->setParticleInputFolder(projectRootFolder + "_input/" + simulationName + "/");

	boolFlag = boolFlag and this->setOutputFolder(projectRootFolder + "_output/" + simulationName + "/");
	boolFlag = boolFlag and this->setNumericalOutputFolder(projectRootFolder + "_output/" + simulationName + "/Numerical/");
	boolFlag = boolFlag and this->setGraphicalOutputFolder(projectRootFolder + "_output/" + simulationName + "/Graphical/");
	boolFlag = boolFlag and this->setTimeVectorOutputFileName("timeVector.txt");
	boolFlag = boolFlag and this->setTimeVectorForPlotOutputFileName("timeVectorForPlot.txt");

	return boolFlag;
}

// ----- Set files -----
bool SimulationFileTree::setSimulationName(const std::string & simulationName)
{
	this->simulationName = simulationName;
	return true;
}

bool SimulationFileTree::setProjectRootFolder(const std::string & projectRootFolder)
{
	return SimulationFileTree::setPathIfPathExists(
			projectRootFolder,
			this->projectRootFolder,
			"Project Root Path",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setInputFolder(const std::string & inputFolder)
{
	return SimulationFileTree::setPathIfPathExists(
			inputFolder,
			this->inputFolder,
			"Input Folder",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setInputMainDataFilePath(const std::string & inputMainDataFilePath)
{
	return SimulationFileTree::setPathIfPathExists(
			inputMainDataFilePath,
			this->inputMainDataFilePath,
			"Main Data Input File Path",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setParticleInputFolder(const std::string & particleInputFolder)
{
	return SimulationFileTree::setPathIfPathExists(
			particleInputFolder,
			this->particleInputFolder,
			"Particle Input Folder",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setOutputFolder(const std::string & outputFolder)
{	
	psin::createDirectory(outputFolder);

	this->outputFolder = outputFolder;

	return psin::checkPathExists(outputFolder);
}

bool SimulationFileTree::setNumericalOutputFolder(const std::string & numericalOutputFolder)
{	
	psin::createDirectory(numericalOutputFolder);

	this->numericalOutputFolder = numericalOutputFolder;

	return psin::checkPathExists(numericalOutputFolder);
}

bool SimulationFileTree::setGraphicalOutputFolder(const std::string & graphicalOutputFolder)
{	
	psin::createDirectory(graphicalOutputFolder);
	psin::createDirectory(graphicalOutputFolder + "Plots/");
	psin::createDirectory(graphicalOutputFolder + "Animations/");

	this->graphicalOutputFolder = graphicalOutputFolder;

	return psin::checkPathExists(graphicalOutputFolder) and psin::checkPathExists(graphicalOutputFolder + "Plots/") and psin::checkPathExists(graphicalOutputFolder + "Animations/");
}

bool SimulationFileTree::setTimeVectorOutputFileName(const std::string & timeVectorOutputFileName)
{
	this->timeVectorOutputFileName = timeVectorOutputFileName;

	this->timeVectorFile.open(this->numericalOutputFolder + timeVectorOutputFileName);

	return !timeVectorFile.fail();
}

bool SimulationFileTree::setTimeVectorForPlotOutputFileName(const std::string & timeVectorForPlotOutputFileName)
{
	this->timeVectorForPlotOutputFileName = timeVectorForPlotOutputFileName;

	this->timeVectorForPlotFile.open(this->numericalOutputFolder + timeVectorForPlotOutputFileName);

	return !timeVectorForPlotFile.fail();
}

// ---- Get files ----
std::string SimulationFileTree::getProjectRootFolder(void) const
{
	return this->projectRootFolder;
}

std::string SimulationFileTree::getInputFolder(void) const
{
	return this->inputFolder;
}

std::string SimulationFileTree::getInputMainDataFilePath(void) const
{
	return this->inputMainDataFilePath;
}

std::string SimulationFileTree::getParticleInputFolder(void) const
{
	return this->particleInputFolder;
}


std::string SimulationFileTree::getOutputFolder(void) const
{
	return this->outputFolder;
}

std::string SimulationFileTree::getNumericalOutputFolder(void) const
{
	return this->numericalOutputFolder;
}

std::string SimulationFileTree::getGraphicalOutputFolder(void) const
{
	return this->graphicalOutputFolder;
}

std::string SimulationFileTree::getTimeVectorOutputFileName(void) const
{
	return this->timeVectorOutputFileName;
}

std::string SimulationFileTree::getTimeVectorForPlotOutputFileName(void) const
{
	return this->timeVectorForPlotOutputFileName;
}


// ---- Validate path ----
bool SimulationFileTree::setPathIfPathExists(const std::string & value, std::string & destination, const std::string & name, const std::string & functionName )
{
	bool checkValue = psin::checkPathExists(value);
	if ( checkValue )
	{
		destination = value;
	}
	else
	{
		std::cerr << std::string("Error in ") + functionName << std::endl
			<< name << " named \"" << value << "\" does not exist" << std::endl;
	}

	return checkValue;
}

} // psin