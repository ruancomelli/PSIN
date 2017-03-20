#include <Simulation.h>

// IOLib
#include <FileReader.h>

// UtilsLib
#include <Debug.h>
#include <FileSystem.h>

// Standard
#include <iostream>
#include <regex>

using std::ofstream;
using std::string;

std::pair<std::string, std::string> Simulation::getSimulationNameAndRootPath(int argc, char **argv)
{
	std::string simulationName = "Simulation1";
	std::string rootPath = parentDirectory( parentDirectory( currentDirectory() ) );

	if(argc > 1)
	{
		std::string argvString;

		for( int i = 1 ; i<=argc ; ++i)
		{
			argvString += argv[i];
			argvString += " ";
		}

		// Find simulation name
		{
			std::regex re("--simulation=\\\"(.*)\\\"");
			std::smatch match;
			std::regex_search(argvString, match, re);
			if (match.size() == 2) {
				simulationName = match.str(1);
			}
		}

		// Find simulation root path
		{
			std::regex re("--root=\\\"(.*)\\\"");
			std::smatch match;
			std::regex_search(argvString, match, re);
			if (match.size() == 2) {
				rootPath = match.str(1);
			}
		}
	}

	return std::pair<std::string, std::string>( simulationName, rootPath );
}

std::string Simulation::getSimulationName(int argc, char **argv)
{
	return Simulation::getSimulationNameAndRootPath(argc, argv).first;
}

std::string Simulation::getSimulationRootPath(int argc, char **argv)
{
	return Simulation::getSimulationNameAndRootPath(argc, argv).second;
}

// ----- Default simulation -----
void Simulation::defaultSimulate(const std::string simulationName, const std::string projectRootFolder)
{
	this->setInputFolder(projectRootFolder + "_input/");
	this->setInputFileName("input.txt");

	this->setName(simulationName);

	this->setInputMainDataFilePath(projectRootFolder + "_input/" + simulationName + "/input.txt");
	this->setParticleInputFolder(projectRootFolder + "_input/" + simulationName + "/");
	this->setOutputFolder(projectRootFolder + "_output/" + simulationName + "/");
	this->setTimeVectorOutputFileName("timeVector.txt");
	this->setTimeVectorForPlotOutputFileName("timeVectorForPlot.txt");

	this->inputMainData();

	this->initializeParticleArray();

	this->outputMainData();

	this->simulate();

	this->printSuccessMessage();
}

// ----- Set and get name -----
void Simulation::setName(const std::string name)
{
	if(!name.empty()) this->name = name;
	else this->name = "Nameless";
}

string Simulation::getName(void) const
{
	return this->name;
}

// ----- Set files -----
bool Simulation::setProjectRootFolder(const std::string projectRootFolder)
{
	bool checkValue = checkPathExists(projectRootFolder);
	if ( checkValue )
	{
		this->projectRootFolder = projectRootFolder;
	}
	else
	{
		std::cerr << std::string("Error in ") + std::string(__CURRENT_FUNCTION__) << std::endl
			<< "Project Root Path named \"" << projectRootFolder << "\" does not exist" << std::endl;
	}

	return checkValue;
}

bool Simulation::setInputFolder(const std::string inputFolder)
{
	bool checkValue = checkPathExists(inputFolder);
	if ( checkValue )
	{
		this->inputFolder = inputFolder;
	}
	else
	{
		std::cerr << std::string("Error in ") + std::string(__CURRENT_FUNCTION__) << std::endl
			<< "Input Folder named \"" << inputFolder << "\" does not exist" << std::endl;
	}

	return checkValue;
}

bool Simulation::setInputFileName(const std::string inputFileName)
{
	bool checkValue = checkPathExists(this->inputFolder + inputFileName);
	if ( checkValue )
	{
		this->inputFileName = inputFileName;
	}
	else
	{
		std::cerr << std::string("Error in ") + std::string(__CURRENT_FUNCTION__) << std::endl
			<< "Input File named \"" << inputFileName << "\" does not exist in \"" << this->inputFolder << "\"" << std::endl;
	}

	return checkValue;
}

bool Simulation::setInputMainDataFilePath(const std::string inputMainDataFilePath)
{
	bool checkValue = checkPathExists(inputMainDataFilePath);
	if ( checkValue )
	{
		this->inputMainDataFilePath = inputMainDataFilePath;
	}
	else
	{
		std::cerr << std::string("Error in ") + std::string(__CURRENT_FUNCTION__) << std::endl
			<< "Main Data Input File Path named \"" << inputMainDataFilePath << "\" does not exist" << std::endl;
	}

	return checkValue;
}

bool Simulation::setParticleInputFolder(const std::string particleInputFolder)
{
	bool checkValue = checkPathExists(particleInputFolder);
	if ( checkValue )
	{
		this->particleInputFolder = particleInputFolder;
	}
	else
	{
		std::cerr << std::string("Error in ") + std::string(__CURRENT_FUNCTION__) << std::endl
			<< "Particle Input Folder named \"" << particleInputFolder << "\" does not exist" << std::endl;
	}

	return checkValue;
}

bool Simulation::setOutputFolder(const std::string outputFolder)
{
	bool boolFlag = ::createDirectory(outputFolder);
	
	if(boolFlag)
	{
		this->outputFolder = outputFolder;
	}

	return boolFlag;
}

bool Simulation::setTimeVectorOutputFileName(const std::string timeVectorOutputFileName)
{
	this->timeVectorOutputFileName = timeVectorOutputFileName;

	this->timeVectorFile.open(this->outputFolder + timeVectorOutputFileName);

	return !timeVectorFile.fail();
}

bool Simulation::setTimeVectorForPlotOutputFileName(const std::string timeVectorForPlotOutputFileName)
{
	this->timeVectorForPlotOutputFileName = timeVectorForPlotOutputFileName;

	this->timeVectorForPlotFile.open(this->outputFolder + timeVectorForPlotOutputFileName);

	return !timeVectorForPlotFile.fail();
}

// ----- Input -----
void Simulation::readName(void)
{
	if( checkPathExists(this->inputFolder + this->inputFileName) )
	{
		FileReader simulationFileReader(this->inputFolder + this->inputFileName);

		std::string simulationName;
		simulationFileReader.readValue("<simulationName>", simulationName);
		this->setName(simulationName);
	}
}

void Simulation::inputMainData(void)
{
	FileReader inputData(this->inputMainDataFilePath);

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
	std::string forceModelName;
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

// ----- Output -----
void Simulation::outputMainData(void)
{
	std::string verticalSeparator = "\n";
	std::string horizontalSeparator = ",";

	std::ofstream mainOutFile(this->outputFolder + "output.txt");
	mainOutFile << "<nParticles> "		<< numberOfParticles	<< verticalSeparator;
	mainOutFile << "<initialTime> "		<< initialTime			<< verticalSeparator;
	mainOutFile << "<timeStep> "		<< timeStep				<< verticalSeparator;
	mainOutFile << "<finalTime> "		<< finalTime			<< verticalSeparator;
	mainOutFile << "<taylorOrder> "		<< taylorOrder			<< verticalSeparator;
	mainOutFile << "<timeStepsForOutput> "	<< timeStepsForOutput		<< verticalSeparator;
	mainOutFile << "<ForceModelName> " << forceModel.getName() << verticalSeparator;
}

void Simulation::printSuccessMessage(void)
{
	std::cout << std::endl << "Success" << std::endl << std::endl;
}

// ForceModel
void Simulation::addForceModel( const ForceModel & fm ){
	this->forceModelSet.insert(fm);
}


// Particles
void Simulation::initializeParticleArray(void)
{
	// Input
	this->particleArray.requireRawPropertyContainer(this->forceModel.getRequiredProperties());

	this->particleArray.inputParticles(this->numberOfParticles, this->particleInputFolder);

	for(auto& particlePtr : particleArray){
		double m = particlePtr->get( PropertyDefinitions::mass );
		double r = particlePtr->getGeometricParameter( RADIUS );

		particlePtr->set( PropertyDefinitions::moment_of_inertia, 2 * m * r * r / 5 );
	}

	particleArray[0]->setGravity(this->gravity);
	particleArray.openFiles(this->outputFolder);

	ForceModel::setNumberOfParticles( this->numberOfParticles );

	for( SphericalParticlePtr particle : particleArray ){
		for( SphericalParticlePtr neighbor : particleArray ){
			if( neighbor->getHandle() > particle->getHandle() ){
				particle->addNeighbor( neighbor );
			}
		}
	}
}

// Simulate
void Simulation::simulate(void)
{
	// Output
	particleArray.exportAllDataCSV();
	this->timeVectorForPlotFile << 0 << "\n";

	// ===== Simulation =====

	int timeStepsForOutputCounter = 0;

	for(double t = initialTime; t <= finalTime ; t += timeStep){

		this->timeVectorFile << t << "\n";

		// Set forces and torques to zero
		for( SphericalParticlePtr particle : particleArray ){
			particle->setContactForce( nullVector3D() );
			particle->setBodyForce( nullVector3D() );
			particle->setResultingTorque( nullVector3D() );
		}

		// Body forces
		for( SphericalParticlePtr particle : particleArray ){
			particle->addBodyForce(particle->get( PropertyDefinitions::mass ) * gravity);
		}

		// Predict position and orientation
		for( SphericalParticlePtr particle : particleArray ){
			particle->setPosition( ForceModel::taylorPredictor( particle->getPosition(), taylorOrder, timeStep ) );
			particle->setOrientation( ForceModel::taylorPredictor( particle->getOrientation(), taylorOrder, timeStep ) );
		}

		// Contact forces
		
		for( SphericalParticlePtr particle : particleArray ){
			for( int handle : particle->getNeighborhood() ){
				SphericalParticlePtr neighbor = particleArray[handle];

				forceModel.calculate(particle, neighbor);
			}
		}

		// Correct position and orientation
		for( SphericalParticlePtr particle : particleArray ){
			ForceModel::correctPosition( particle , taylorOrder, timeStep );
			ForceModel::correctOrientation( particle , taylorOrder, timeStep );
		}


		// ----- Saving to file -----

		// Prints every derivative of particles' position
		if( (++timeStepsForOutputCounter) == timeStepsForOutput){
			timeStepsForOutputCounter = 0;

			particleArray.exportTemporalDataCSV();

			this->timeVectorForPlotFile << t << "\n";
		}
	}
}