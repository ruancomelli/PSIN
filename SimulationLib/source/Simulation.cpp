#include <Simulation.h>

// IOLib
#include <FileReader.h>

// UtilsLib
#include <Debug.h>
#include <FileSystem.h>

// Simulation::Simulation(const string projectRootPath)
// {
// 	string inputFolder = projectRootPath + "_input/";

// 	if( checkPathExists(inputFolder) )
// 	{
// 		this->inputFolder = inputFolder;

// 		FileReader simulationFileReader(inputFolder + "input.txt");
// 		string simulationName;
// 		if( simulationFileReader.readValue("<simulationName>", simulationName) )
// 		{
// 			this->setName(simulationName);
// 			this->outputFolder = projectRootPath + "_output/" + simulationName + "/";
// 			this->particleInputFolder = inputFolder + simulationName + "/";

// 			::createDirectory(this->outputFolder);
// 			::createDirectory(this->outputFolder + "MATLAB_output/");

// 			this->isReady = true;
// 		}
// 		else
// 		{
// 			this->setName("");
// 		}
// 	} 
// 	else
// 	{
// 		cerr << string("Error in ") + string(__CURRENT_FUNCTION__) << endl
// 			<< "Input Folder named \"" << inputFolder << "\" does not exist" << endl;
// 	}
// }

// ----- Set and get name -----
void Simulation::setName(const string name)
{
	if(!name.empty()) this->name = name;
	else this->name = "Nameless";
}

string Simulation::getName(void) const
{
	return this->name;
}

// ----- Set files -----
bool Simulation::setProjectRootFolder(const string projectRootFolder)
{
	bool checkValue = checkPathExists(projectRootFolder);
	if ( checkValue )
	{
		this->projectRootFolder = projectRootFolder;
	}
	else
	{
		cerr << string("Error in ") + string(__CURRENT_FUNCTION__) << endl
			<< "Project Root Path named \"" << projectRootFolder << "\" does not exist" << endl;
	}

	return checkValue;
}

bool Simulation::setInputFolder(const string inputFolder)
{
	bool checkValue = checkPathExists(inputFolder);
	if ( checkValue )
	{
		this->inputFolder = inputFolder;
	}
	else
	{
		cerr << string("Error in ") + string(__CURRENT_FUNCTION__) << endl
			<< "Input Folder named \"" << inputFolder << "\" does not exist" << endl;
	}

	return checkValue;
}

bool Simulation::setInputFileName(const string inputFileName)
{
	bool checkValue = checkPathExists(this->inputFolder + inputFileName);
	if ( checkValue )
	{
		this->inputFileName = inputFileName;
	}
	else
	{
		cerr << string("Error in ") + string(__CURRENT_FUNCTION__) << endl
			<< "Input File named \"" << inputFileName << "\" does not exist in \"" << this->inputFolder << "\"" << endl;
	}

	return checkValue;
}

bool Simulation::setInputMainDataFilePath(const string inputMainDataFilePath)
{
	bool checkValue = checkPathExists(inputMainDataFilePath);
	if ( checkValue )
	{
		this->inputMainDataFilePath = inputMainDataFilePath;
	}
	else
	{
		cerr << string("Error in ") + string(__CURRENT_FUNCTION__) << endl
			<< "Main Data Input File Path named \"" << inputMainDataFilePath << "\" does not exist" << endl;
	}

	return checkValue;
}

bool Simulation::setParticleInputFolder(const string particleInputFolder)
{
	bool checkValue = checkPathExists(particleInputFolder);
	if ( checkValue )
	{
		this->particleInputFolder = particleInputFolder;
	}
	else
	{
		cerr << string("Error in ") + string(__CURRENT_FUNCTION__) << endl
			<< "Particle Input Folder named \"" << particleInputFolder << "\" does not exist" << endl;
	}

	return checkValue;
}

bool Simulation::setOutputFolder(const string outputFolder)
{
	bool boolFlag = ::createDirectory(outputFolder);
	
	if(boolFlag)
	{
		this->outputFolder = outputFolder;
	}

	return boolFlag;
}

bool Simulation::setTimeVectorOutputFileName(const string timeVectorOutputFileName)
{
	this->timeVectorOutputFileName = timeVectorOutputFileName;

	this->timeVectorFile.open(this->outputFolder + timeVectorOutputFileName);

	return !timeVectorFile.fail();
}

bool Simulation::setTimeVectorForPlotOutputFileName(const string timeVectorForPlotOutputFileName)
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

		string simulationName;
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

// ----- Output -----
void Simulation::outputMainData(void)
{
	string verticalSeparator = "\n";
	string horizontalSeparator = ",";

	ofstream mainOutFile(this->outputFolder + "output.txt");
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
	cout << endl << "Success" << endl << endl;
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
		double m = particlePtr->get( mass );
		double r = particlePtr->getGeometricParameter( RADIUS );

		particlePtr->set( moment_of_inertia, 2 * m * r * r / 5 );
	}

	particleArray[0]->setGravity(this->gravity);
	particleArray.openFiles(this->outputFolder);

	ForceModel::setNumberOfParticles( this->numberOfParticles );

	foreach( SphericalParticlePtr particle, particleArray ){
		foreach( SphericalParticlePtr neighbor, particleArray ){
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
		foreach( SphericalParticlePtr particle, particleArray ){
			particle->setContactForce( nullVector3D() );
			particle->setBodyForce( nullVector3D() );
			particle->setResultingTorque( nullVector3D() );
		}

		// Body forces
		foreach( SphericalParticlePtr particle, particleArray ){
			particle->addBodyForce(particle->get( mass ) * gravity);
		}

		// Predict position and orientation
		foreach( SphericalParticlePtr particle, particleArray ){
			particle->setPosition( ForceModel::taylorPredictor( particle->getPosition(), taylorOrder, timeStep ) );
			particle->setOrientation( ForceModel::taylorPredictor( particle->getOrientation(), taylorOrder, timeStep ) );
		}

		// Contact forces
		
		foreach( SphericalParticlePtr particle, particleArray ){
			foreach( int handle, particle->getNeighborhood() ){
				SphericalParticlePtr neighbor = particleArray[handle];

				forceModel.calculate(particle, neighbor);
			}
		}

		// Correct position and orientation
		foreach( SphericalParticlePtr particle, particleArray ){
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