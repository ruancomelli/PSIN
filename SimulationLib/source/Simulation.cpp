#include <Simulation.hpp>

// IOLib
#include <FileReader.hpp>

// UtilsLib
#include <Debug.hpp>
#include <FileSystem.hpp>
#include <ProgramOptions.hpp>

// Standard
#include <iostream>
#include <regex>

using std::ofstream;
using std::string;

std::pair<std::string, std::string> Simulation::getSimulationNameAndRootPath(int argc, char **argv)
{
	std::string simulationName = "Simulation1";
	std::string rootPath = parentDirectory( parentDirectory( currentDirectory() ) );

	ProgramOptions::OptionsDescription desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("simulation", ProgramOptions::value<std::string>(), "simulation's name")
		("root", ProgramOptions::value<std::string>(), "simulation's root folder")
	;

	ProgramOptions::VariablesMap vm = parseCommandLine(argc, argv, desc);

	if(vm.count("help"))
	{
		std::cout << desc << "\n";
		exit(0);
	}

	if(vm.count("simulation"))
	{
		simulationName = vm["simulation"].as<string>();
	}

	if(vm.count("root"))
	{
		rootPath = vm["root"].as<string>();
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
void Simulation::defaultSimulate(const string simulationName, const string projectRootFolder)
{
	this->setProjectRootFolder(projectRootFolder);
	this->setInputFolder(projectRootFolder + "_input/");

	this->setName(simulationName);

	this->setInputMainDataFilePath(projectRootFolder + "_input/" + simulationName + "/mainInfoInput.txt");
	this->setParticleInputFolder(projectRootFolder + "_input/" + simulationName + "/");

	this->setOutputFolder(projectRootFolder + "_output/" + simulationName + "/");
	this->setNumericalOutputFolder(projectRootFolder + "_output/" + simulationName + "/Numerical/");
	this->setGraphicalOutputFolder(projectRootFolder + "_output/" + simulationName + "/Graphical/");
	this->setTimeVectorOutputFileName("timeVector.txt");
	this->setTimeVectorForPlotOutputFileName("timeVectorForPlot.txt");

	this->inputMainData();

	this->initializeParticleArray();

	this->outputMainData();

	this->simulate();

	this->printSuccessMessage();
}

// ----- Set files -----
bool Simulation::checkPathExistance(const string value, string & destination, const string name, const string functionName )
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

bool Simulation::setProjectRootFolder(const std::string projectRootFolder)
{
	return Simulation::checkPathExistance(
			projectRootFolder,
			this->projectRootFolder,
			"Project Root Path",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool Simulation::setInputFolder(const std::string inputFolder)
{
	return Simulation::checkPathExistance(
			inputFolder,
			this->inputFolder,
			"Input Folder",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool Simulation::setInputMainDataFilePath(const std::string inputMainDataFilePath)
{
	return Simulation::checkPathExistance(
			inputMainDataFilePath,
			this->inputMainDataFilePath,
			"Main Data Input File Path",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool Simulation::setParticleInputFolder(const std::string particleInputFolder)
{
	return Simulation::checkPathExistance(
			particleInputFolder,
			this->particleInputFolder,
			"Particle Input Folder",
			std::string(__CURRENT_FUNCTION__)
		);
}

bool Simulation::setOutputFolder(const std::string outputFolder)
{	
	::createDirectory(outputFolder);

	this->outputFolder = outputFolder;

	return true;
}

bool Simulation::setNumericalOutputFolder(const std::string numericalOutputFolder)
{	
	::createDirectory(numericalOutputFolder);

	this->numericalOutputFolder = numericalOutputFolder;

	return true;
}

bool Simulation::setGraphicalOutputFolder(const std::string graphicalOutputFolder)
{	
	::createDirectory(graphicalOutputFolder);
	::createDirectory(graphicalOutputFolder + "Plots/");
	::createDirectory(graphicalOutputFolder + "Animations/");

	this->graphicalOutputFolder = graphicalOutputFolder;

	return true;
}

bool Simulation::setTimeVectorOutputFileName(const std::string timeVectorOutputFileName)
{
	this->timeVectorOutputFileName = timeVectorOutputFileName;

	this->timeVectorFile.open(this->numericalOutputFolder + timeVectorOutputFileName);

	return !timeVectorFile.fail();
}

bool Simulation::setTimeVectorForPlotOutputFileName(const std::string timeVectorForPlotOutputFileName)
{
	this->timeVectorForPlotOutputFileName = timeVectorForPlotOutputFileName;

	this->timeVectorForPlotFile.open(this->numericalOutputFolder + timeVectorForPlotOutputFileName);

	return !timeVectorForPlotFile.fail();
}

// ----- Input -----
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
void Simulation::outputMainData(void) const
{
	std::string verticalSeparator = "\n";
	std::string horizontalSeparator = ",";

	std::ofstream mainOutFile(this->numericalOutputFolder + "mainInfoOutput.txt");

	mainOutFile << "<nParticles> "		<< numberOfParticles	<< verticalSeparator;
	mainOutFile << "<initialTime> "		<< initialTime			<< verticalSeparator;
	mainOutFile << "<timeStep> "		<< timeStep				<< verticalSeparator;
	mainOutFile << "<finalTime> "		<< finalTime			<< verticalSeparator;
	mainOutFile << "<taylorOrder> "		<< taylorOrder			<< verticalSeparator;
	mainOutFile << "<timeStepsForOutput> "	<< timeStepsForOutput		<< verticalSeparator;
	mainOutFile << "<ForceModelName> " << forceModel.getName() << verticalSeparator;
}

void Simulation::printSuccessMessage(void) const
{
	std::cout << std::endl << "Success" << std::endl << std::endl;
}

// ForceModel
void Simulation::addForceModel( const ForceModel<SphericalParticle, SphericalParticle> & fm ){
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
	particleArray.openFiles(this->numericalOutputFolder);

	ForceModel<SphericalParticle, SphericalParticle>::setNumberOfParticles( this->numberOfParticles );

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
			particle->setPosition( ForceModel<SphericalParticle, SphericalParticle>::taylorPredictor( particle->getPosition(), taylorOrder, timeStep ) );
			particle->setOrientation( ForceModel<SphericalParticle, SphericalParticle>::taylorPredictor( particle->getOrientation(), taylorOrder, timeStep ) );
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
			ForceModel<SphericalParticle, SphericalParticle>::correctPosition( particle , taylorOrder, timeStep );
			ForceModel<SphericalParticle, SphericalParticle>::correctOrientation( particle , taylorOrder, timeStep );
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