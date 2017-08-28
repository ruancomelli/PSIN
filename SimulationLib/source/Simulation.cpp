// #include <Simulation.hpp>

// // IOLib
// #include <FileReader.hpp>

// // PropertyLib
// #include <PropertyDefinitions.hpp>

// // UtilsLib
// #include <FileSystem.hpp>
// #include <ProgramOptions.hpp>

// // ----- Default simulation -----
// void Simulation::defaultSimulate(const string simulationName, const string projectRootFolder)
// {
// 	this->setName(simulationName);
// 	this->fileTree.setTree(simulationName, projectRootFolder);

// 	this->inputMainData();

// 	this->initializeParticleArray();

// 	this->outputMainData();

// 	this->simulate();

// 	this->printSuccessMessage();
// }

// // Simulate
// void Simulation::simulate(void)
// {
// 	// Output
// 	particleArray.exportAllDataCSV();
// 	this->fileTree.timeVectorForPlotFile << 0 << "\n";

// 	// ===== Simulation =====

// 	int timeStepsForOutputCounter = 0;

// 	for(double t = initialTime; t <= finalTime ; t += timeStep){

// 		this->fileTree.timeVectorFile << t << "\n";

// 		// Set forces and torques to zero
// 		for( SphericalParticlePtr particle : particleArray ){
// 			particle->setContactForce( nullVector3D() );
// 			particle->setBodyForce( nullVector3D() );
// 			particle->setResultingTorque( nullVector3D() );
// 		}

// 		// Body forces
// 		for( SphericalParticlePtr particle : particleArray ){
// 			particle->addBodyForce(particle->get( PropertyDefinitions::mass ) * gravity);
// 		}

// 		// Predict position and orientation
// 		for( SphericalParticlePtr particle : particleArray ){
// 			particle->setPosition( Interaction<SphericalParticle, SphericalParticle>::taylorPredictor( particle->getPosition(), taylorOrder, timeStep ) );
// 			particle->setOrientation( Interaction<SphericalParticle, SphericalParticle>::taylorPredictor( particle->getOrientation(), taylorOrder, timeStep ) );
// 		}

// 		// Contact forces
		
// 		for( SphericalParticlePtr particle : particleArray ){
// 			for( int handle : particle->getNeighborhood() ){
// 				SphericalParticlePtr neighbor = particleArray[handle];

// 				Interaction.calculate(particle, neighbor);
// 			}
// 		}

// 		// Correct position and orientation
// 		for( SphericalParticlePtr particle : particleArray ){
// 			Interaction<SphericalParticle, SphericalParticle>::correctPosition( particle , taylorOrder, timeStep );
// 			Interaction<SphericalParticle, SphericalParticle>::correctOrientation( particle , taylorOrder, timeStep );
// 		}


// 		// ----- Saving to file -----

// 		// Prints every derivative of particles' position
// 		if( (++timeStepsForOutputCounter) == timeStepsForOutput){
// 			timeStepsForOutputCounter = 0;

// 			particleArray.exportTemporalDataCSV();

// 			this->fileTree.timeVectorForPlotFile << t << "\n";
// 		}
// 	}
// }

// // ----- Input -----
// void Simulation::inputMainData(void)
// {
// 	FileReader inputData(this->fileTree.getInputMainDataFilePath());

// 	// Read simulation data
// 	inputData.readValue("<initialTime>", this->initialTime);
// 	inputData.readValue("<timeStep>", this->timeStep);
// 	inputData.readValue("<finalTime>", this->finalTime);
// 	inputData.readValue("<taylorOrder>", this->taylorOrder);
// 	inputData.readValue("<dimension>", this->dimension);
// 	inputData.readValue("<numberOfParticles>", this->numberOfParticles);
// 	inputData.readValue("<gravity>", this->gravity);
// 	inputData.readValue("<timeStepsForOutput>", this->timeStepsForOutput);

// 	// Read Interaction
// 	std::string InteractionName;
// 	inputData.readValue("<InteractionName>", InteractionName);

// 	this->setInteraction(InteractionName);
// }

// // ----- Output -----
// void Simulation::outputMainData(void) const
// {
// 	std::string verticalSeparator = "\n";
// 	std::string horizontalSeparator = ",";

// 	std::ofstream mainOutFile(this->fileTree.getNumericalOutputFolder() + "mainInfoOutput.txt");

// 	mainOutFile << "<nParticles> "		<< numberOfParticles	<< verticalSeparator;
// 	mainOutFile << "<initialTime> "		<< initialTime			<< verticalSeparator;
// 	mainOutFile << "<timeStep> "		<< timeStep				<< verticalSeparator;
// 	mainOutFile << "<finalTime> "		<< finalTime			<< verticalSeparator;
// 	mainOutFile << "<taylorOrder> "		<< taylorOrder			<< verticalSeparator;
// 	mainOutFile << "<timeStepsForOutput> "	<< timeStepsForOutput		<< verticalSeparator;
// 	mainOutFile << "<InteractionName> " << Interaction.getName() << verticalSeparator;
// }


// // Particles
// void Simulation::initializeParticleArray(void)
// {
// 	// Input
// 	this->particleArray.requirePropertyContainer(this->Interaction.getRequiredProperties());

// 	this->particleArray.inputParticles(this->numberOfParticles, this->fileTree.getParticleInputFolder());

// 	for(auto& particlePtr : particleArray){
// 		double m = particlePtr->get( PropertyDefinitions::mass );
// 		double r = particlePtr->getGeometricParameter( RADIUS );

// 		particlePtr->set( PropertyDefinitions::moment_of_inertia, 2 * m * r * r / 5 );
// 	}

// 	particleArray[0]->setGravity(this->gravity);
// 	particleArray.openFiles(this->fileTree.getNumericalOutputFolder());

// 	Interaction<SphericalParticle, SphericalParticle>::setNumberOfParticles( this->numberOfParticles );

// 	for( SphericalParticlePtr particle : particleArray ){
// 		for( SphericalParticlePtr neighbor : particleArray ){
// 			if( neighbor->getHandle() > particle->getHandle() ){
// 				particle->addNeighbor( neighbor );
// 			}
// 		}
// 	}
// }

// // Interaction
// void Simulation::setInteraction(const std::string & InteractionName)
// {
// 	for (auto& fm : this->InteractionSet)
// 	{
// 		if (fm.getName() == InteractionName)
// 		{
// 			this->Interaction = fm;
// 			break;
// 		}
// 	}
// }

// void Simulation::appendInteraction( const Interaction<SphericalParticle, SphericalParticle> & fm ){
// 	this->InteractionSet.insert(fm);
// }

// // Parse command line
// std::string Simulation::parseArgvIntoSimulationName(int argc, char **argv)
// {
// 	return Simulation::parseArgvIntoSimulationNameAndRootPath(argc, argv).first;
// }

// std::string Simulation::parseArgvIntoSimulationRootPath(int argc, char **argv)
// {
// 	return Simulation::parseArgvIntoSimulationNameAndRootPath(argc, argv).second;
// }

// std::pair<std::string, std::string> Simulation::parseArgvIntoSimulationNameAndRootPath(int argc, char **argv)
// {
// 	std::string simulationName = "Simulation1";
// 	std::string rootPath = parentDirectory( parentDirectory( currentDirectory() ) );

// 	ProgramOptions::OptionsDescription desc("Allowed options");
// 	desc.add_options()
// 		("help", "produce help message")
// 		("simulation", ProgramOptions::value<std::string>(), "simulation's name")
// 		("root", ProgramOptions::value<std::string>(), "simulation's root folder")
// 	;

// 	ProgramOptions::VariablesMap vm = parseCommandLine(argc, argv, desc);

// 	if(vm.count("help"))
// 	{
// 		std::cout << desc << "\n";
// 		exit(0);
// 	}

// 	if(vm.count("simulation"))
// 	{
// 		simulationName = vm["simulation"].as<string>();
// 	}

// 	if(vm.count("root"))
// 	{
// 		rootPath = vm["root"].as<string>();
// 	}

// 	return std::pair<std::string, std::string>( simulationName, rootPath );
// }

// // Ending simulation
// void Simulation::printSuccessMessage(void) const
// {
// 	std::cout << std::endl << "Success" << std::endl << std::endl;
// }