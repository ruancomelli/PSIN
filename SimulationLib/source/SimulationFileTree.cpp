#include <Simulation.hpp>

// UtilsLib
#include <Debug.hpp>
#include <FileSystem.hpp>


// ----- Set files -----
bool SimulationFileTree::setProjectRootFolder(const string & projectRootFolder)
{
	return SimulationFileTree::setPathIfPathExists(
			projectRootFolder,
			this->projectRootFolder,
			"Project Root Path",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setInputFolder(const string & inputFolder)
{
	return SimulationFileTree::setPathIfPathExists(
			inputFolder,
			this->inputFolder,
			"Input Folder",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setInputMainDataFilePath(const string & inputMainDataFilePath)
{
	return SimulationFileTree::setPathIfPathExists(
			inputMainDataFilePath,
			this->inputMainDataFilePath,
			"Main Data Input File Path",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool SimulationFileTree::setParticleInputFolder(const string & particleInputFolder)
{
	return SimulationFileTree::setPathIfPathExists(
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

	return ::checkPathExists(outputFolder);
}

bool SimulationFileTree::setNumericalOutputFolder(const string & numericalOutputFolder)
{	
	::createDirectory(numericalOutputFolder);

	this->numericalOutputFolder = numericalOutputFolder;

	return ::checkPathExists(numericalOutputFolder);
}

bool SimulationFileTree::setGraphicalOutputFolder(const string & graphicalOutputFolder)
{	
	::createDirectory(graphicalOutputFolder);
	::createDirectory(graphicalOutputFolder + "Plots/");
	::createDirectory(graphicalOutputFolder + "Animations/");

	this->graphicalOutputFolder = graphicalOutputFolder;

	return ::checkPathExists(graphicalOutputFolder) && ::checkPathExists(graphicalOutputFolder + "Plots/") && ::checkPathExists(graphicalOutputFolder + "Animations/");
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
	return this->inputMainDataFilePath;
}

string SimulationFileTree::getParticleInputFolder(void) const
{
	return this->particleInputFolder;
}


string SimulationFileTree::getOutputFolder(void) const
{
	return this->outputFolder;
}

string SimulationFileTree::getNumericalOutputFolder(void) const
{
	return this->numericalOutputFolder;
}

string SimulationFileTree::getGraphicalOutputFolder(void) const
{
	return this->graphicalOutputFolder;
}

string SimulationFileTree::getTimeVectorOutputFileName(void) const
{
	return this->timeVectorOutputFileName;
}

string SimulationFileTree::getTimeVectorForPlotOutputFileName(void) const
{
	return this->timeVectorForPlotOutputFileName;
}


// ---- Validate path ----
bool SimulationFileTree::setPathIfPathExists(const string & value, string & destination, const string & name, const string & functionName )
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