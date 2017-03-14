#include <Simulation.h>

// ForceModelLib
#include <ForceModelSet.h>

// IOLib
#include <FileReader.h>

// UtilsLib
#include <Debug.h>
#include <FileSystem.h>

void Simulation::doItAll(const string project_root_path)
{
	ForceModel viscoelasticSpheres("ViscoElasticSpheres");
	viscoelasticSpheres.setNormal( normalForceViscoelasticSpheres );
	viscoelasticSpheres.setTangential( tangentialForceHaffWerner );
	viscoelasticSpheres.requireProperty(mass);
	viscoelasticSpheres.requireProperty(moment_of_inertia);
	viscoelasticSpheres.requireProperty(elastic_modulus);
	viscoelasticSpheres.requireProperty(dissipative_constant);
	viscoelasticSpheres.requireProperty(poisson_ratio);
	viscoelasticSpheres.requireProperty(tangential_damping);
	viscoelasticSpheres.requireProperty(friction_parameter);

	forceModelSet.insert( viscoelasticSpheres );


	ForceModel electrostatic("Electrostatic");
	electrostatic.setField(electrostaticForce);
	electrostatic.setNormal( normalForceViscoelasticSpheres );
	electrostatic.setTangential( tangentialForceHaffWerner );
	electrostatic.requireProperty(mass);
	electrostatic.requireProperty(moment_of_inertia);
	electrostatic.requireProperty(elastic_modulus);
	electrostatic.requireProperty(dissipative_constant);
	electrostatic.requireProperty(poisson_ratio);
	electrostatic.requireProperty(tangential_damping);
	electrostatic.requireProperty(friction_parameter);
	electrostatic.requireProperty(electric_charge);

	forceModelSet.insert( electrostatic );



	int defaultDimension = 3; // This means that we are constrained to Vector3D

	// Simulation data
	string inputFolder(project_root_path + "_input/");	//
	FileReader simulationFileReader(inputFolder + "input.txt");	//
	string simulationName;	//
	simulationFileReader.readValue("<simulationName>", simulationName);	//

	FileReader inputData(inputFolder + simulationName + "/input.txt");	//
	double initialTime; //
	double timeStep; //
	double finalTime; //
	int taylorOrder; //
	int dimension; //
	int numberOfParticles; //
	int timeStepsForOutput; //
	string forceModelName; //
	Vector3D gravity; //

	inputData.readValue("<initialTime>", initialTime); //
	inputData.readValue("<timeStep>", timeStep); //
	inputData.readValue("<finalTime>", finalTime); //
	inputData.readValue("<taylorOrder>", taylorOrder); //
	inputData.readValue("<dimension>", dimension); //
	inputData.readValue("<numberOfParticles>", numberOfParticles); //
	inputData.readValue("<gravity>", gravity); //
	inputData.readValue("<timeStepsForOutput>", timeStepsForOutput); //
	inputData.readValue("<ForceModelName>", forceModelName); //

	string outputPath(project_root_path + "_output/" + simulationName + "/"); 

	createDirectory(outputPath);
	createDirectory(outputPath + "MATLAB_output/");

	ForceModel forceModel; //

	for (auto& fm : forceModelSet) //
	{
		if (fm.getName() == forceModelName) //
		{
			forceModel = fm; //
			break; //
		}
	}

	// Input
	string particleInputFolder(inputFolder + simulationName + "/");

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
	particleArray.openFiles(outputPath);
	
	string verticalSeparator = "\n";
	string horizontalSeparator = ",";

	ofstream mainOutFile(outputPath + "output.txt");
	mainOutFile << "<nParticles> "		<< numberOfParticles	<< verticalSeparator;
	mainOutFile << "<initialTime> "		<< initialTime			<< verticalSeparator;
	mainOutFile << "<timeStep> "		<< timeStep				<< verticalSeparator;
	mainOutFile << "<finalTime> "		<< finalTime			<< verticalSeparator;
	mainOutFile << "<taylorOrder> "		<< taylorOrder			<< verticalSeparator;
	mainOutFile << "<timeStepsForOutput> "	<< timeStepsForOutput		<< verticalSeparator;
	mainOutFile << "<ForceModelName> " << forceModel.getName() << verticalSeparator;

	ofstream timeVectorFile(outputPath + "timeVector.txt");
	ofstream timeVectorForPlotFile(outputPath + "timeVectorForPlot.txt");

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

Simulation::Simulation(const string projectRootPath)
{
	string inputFolder = projectRootPath + "_input/";

	if( checkPathExists(inputFolder) )
	{
		this->inputFolder = inputFolder;

		FileReader simulationFileReader(inputFolder + "input.txt");
		string simulationName;
		if( simulationFileReader.readValue("<simulationName>", simulationName) )
		{
			this->setName(simulationName);
			this->outputPath = projectRootPath + "_output/" + simulationName + "/";
			this->particleInputFolder = inputFolder + simulationName + "/";

			::createDirectory(this->outputPath);
			::createDirectory(this->outputPath + "MATLAB_output/");

			this->isReady = true;
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