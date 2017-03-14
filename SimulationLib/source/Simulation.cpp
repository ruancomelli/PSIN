#include <Simulation.h>

// IOLib
#include <FileReader.h>

// UtilsLib
#include <Debug.h>
#include <FileSystem.h>

void Simulation::doItAll(const string project_root_path)
{
	int defaultDimension = 3; // This means that we are constrained to Vector3D

	// Simulation data
	string simulationName = this->getName();

	FileReader inputData(this->inputFolder + simulationName + "/input.txt");
	double initialTime;
	double timeStep;
	double finalTime;
	int taylorOrder;
	int dimension;
	int numberOfParticles;
	int timeStepsForOutput;
	string forceModelName;
	Vector3D gravity;

	inputData.readValue("<initialTime>", initialTime);
	inputData.readValue("<timeStep>", timeStep);
	inputData.readValue("<finalTime>", finalTime);
	inputData.readValue("<taylorOrder>", taylorOrder);
	inputData.readValue("<dimension>", dimension);
	inputData.readValue("<numberOfParticles>", numberOfParticles);
	inputData.readValue("<gravity>", gravity);
	inputData.readValue("<timeStepsForOutput>", timeStepsForOutput);
	inputData.readValue("<ForceModelName>", forceModelName);

	createDirectory(this->outputFolder);
	createDirectory(this->outputFolder + "MATLAB_output/");

	ForceModel forceModel;

	for (auto& fm : this->forceModelSet)
	{
		if (fm.getName() == forceModelName)
		{
			forceModel = fm;
			break;
		}
	}

	// Input
	string particleInputFolder(this->inputFolder + simulationName + "/");

	SphericalParticlePtrArrayKit particleArray;

	particleArray.requireRawPropertyContainer(forceModel.getRequiredProperties());

	particleArray.inputParticles(numberOfParticles, particleInputFolder);

	for(auto& particlePtr : particleArray){
		double m = particlePtr->get( mass );
		double r = particlePtr->getGeometricParameter( RADIUS );

		particlePtr->set( moment_of_inertia, 2 * m * r * r / 5 );
	}

	particleArray[0]->setGravity(gravity);
	
	// Output
	particleArray.openFiles(this->outputFolder);
	
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

	ofstream timeVectorFile(this->outputFolder + "timeVector.txt");
	ofstream timeVectorForPlotFile(this->outputFolder + "timeVectorForPlot.txt");

	particleArray.exportAllDataCSV();
	timeVectorForPlotFile << 0 << verticalSeparator;

	// ===== Simulation =====
	ForceModel::setNumberOfParticles( numberOfParticles );

	foreach( SphericalParticlePtr particle, particleArray ){
		foreach( SphericalParticlePtr neighbor, particleArray ){
			if( neighbor->getHandle() > particle->getHandle() ){
				particle->addNeighbor( neighbor );
			}
		}
	}

	int timeStepsForOutputCounter = 0;

	for(double t = initialTime; t <= finalTime ; t += timeStep){

		timeVectorFile << t << verticalSeparator;

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

			timeVectorForPlotFile << t << verticalSeparator;
		}
	}

	mainOutFile.close();
	timeVectorFile.close();
	timeVectorForPlotFile.close();
	
	cout << endl << "Success" << endl << endl;
}

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

// Set and get name
void Simulation::readName(void)
{
	if( checkPathExists(this->inputFolder + "input.txt") )
	{
		FileReader simulationFileReader(this->inputFolder + "input.txt");

		string simulationName;
		simulationFileReader.readValue("<simulationName>", simulationName);
		this->setName(simulationName);
	}
}

void Simulation::setName(const string name)
{
	if(!name.empty()) this->name = name;
	else this->name = "Nameless";
}

string Simulation::getName(void) const
{
	return this->name;
}

// Input main data
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

// Set files' paths
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
	bool checkValue = checkPathExists(outputFolder);
	if ( checkValue )
	{
		this->outputFolder = outputFolder;
	}
	else
	{
		cerr << string("Error in ") + string(__CURRENT_FUNCTION__) << endl
			<< "Output Path named \"" << outputFolder << "\" does not exist" << endl;
	}

	return checkValue;
}

// ForceModel
void Simulation::addForceModel( const ForceModel & fm ){
	this->forceModelSet.insert(fm);
}