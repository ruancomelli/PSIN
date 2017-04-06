#include <Simulation.hpp>

// UtilsLib
#include <Debug.hpp>
#include <FileSystem.hpp>


// ----- Set files -----
bool SimulationFileTree::setProjectRootFolder(const string & projectRootFolder)
{
	return SimulationFileTree::checkPathExistance(
			projectRootFolder,
			this->projectRootFolder,
			"Project Root Path",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setInputFolder(const string & inputFolder)
{
	return SimulationFileTree::checkPathExistance(
			inputFolder,
			this->inputFolder,
			"Input Folder",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setInputMainDataFilePath(const string & inputMainDataFilePath)
{
	return SimulationFileTree::checkPathExistance(
			inputMainDataFilePath,
			this->inputMainDataFilePath,
			"Main Data Input File Path",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setParticleInputFolder(const string & particleInputFolder)
{
	return SimulationFileTree::checkPathExistance(
			particleInputFolder,
			this->particleInputFolder,
			"Particle Input Folder",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setOutputFolder(const string & outputFolder)
{	
	::createDirectory(outputFolder);

	this->outputFolder = outputFolder;

	return true;
}

bool SimulationFileTree::setNumericalOutputFolder(const string & numericalOutputFolder)
{	
	::createDirectory(numericalOutputFolder);

	this->numericalOutputFolder = numericalOutputFolder;

	return true;
}

bool SimulationFileTree::setGraphicalOutputFolder(const string & graphicalOutputFolder)
{	
	::createDirectory(graphicalOutputFolder);
	::createDirectory(graphicalOutputFolder + "Plots/");
	::createDirectory(graphicalOutputFolder + "Animations/");

	this->graphicalOutputFolder = graphicalOutputFolder;

	return true;
}

bool SimulationFileTree::setTimeVectorOutputFileName(const string & timeVectorOutputFileName)
{
	this->timeVectorOutputFileName = timeVectorOutputFileName;

	this->timeVectorFile.open(this->numericalOutputFolder + timeVectorOutputFileName);

	return !timeVectorFile.fail();
}

bool SimulationFileTree::setTimeVectorForPlotOutputFileName(const string & timeVectorForPlotOutputFileName)
{
	this->timeVectorForPlotOutputFileName = timeVectorForPlotOutputFileName;

	this->timeVectorForPlotFile.open(this->numericalOutputFolder + timeVectorForPlotOutputFileName);

	return !timeVectorForPlotFile.fail();
}

// ---- Get files ----
string SimulationFileTree::getProjectRootFolder(void) const
{
	return this->projectRootFolder;
}

string SimulationFileTree::getInputFolder(void) const
{
	return this->inputFolder;
}

string SimulationFileTree::getInputMainDataFilePath(void) const
{
	return inputMainDataFilePath;
}

string SimulationFileTree::getParticleInputFolder(void) const
{
	return particleInputFolder;
}


string SimulationFileTree::getOutputFolder(void) const
{
	return outputFolder;
}

string SimulationFileTree::getNumericalOutputFolder(void) const
{
	return numericalOutputFolder;
}

string SimulationFileTree::getGraphicalOutputFolder(void) const
{
	return graphicalOutputFolder;
}

string SimulationFileTree::getTimeVectorOutputFileName(void) const
{
	return timeVectorOutputFileName;
}

string SimulationFileTree::getTimeVectorForPlotOutputFileName(void) const
{
	return timeVectorForPlotOutputFileName;
}



// ---- Validate path ----
bool SimulationFileTree::checkPathExistance(const string & value, string & destination, const string & name, const string & functionName )
{
	bool checkValue = ::checkPathExists(value);
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