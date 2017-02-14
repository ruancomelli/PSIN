// ==============================================================================================================================
// File setup
// ==============================================================================================================================
// The following pseudo-code line represents every include we want
#include <everything>

using namespace std;

// This is main function
using boost::math::constants::pi;

const string project_root_path = PROJECT_PATH;


// ==============================================================================================================================
// Main function
// ==============================================================================================================================
// Main function is the simulator. Obviously, this can be changed later, 

int main(int argc, char **argv){

	// Simulation data
	string inputFolder(project_root_path + "_input/");
	FileReader simulationFileReader(inputFolder + "input.txt");
	string simulationName;
	simulationFileReader.readValue("<simulationName>", simulationName);

	FileReader inputData(inputFolder + simulationName + "/input.txt");
	double initialTime;
	double timeStep;
	double finalTime;
	int taylorOrder;
	int dimension;
	int numberOfParticles;
	int timeStepsForOutput;
	Vector3D gravity;

	inputData.readValue("<initialTime>", initialTime);
	inputData.readValue("<timeStep>", timeStep);
	inputData.readValue("<finalTime>", finalTime);
	inputData.readValue("<taylorOrder>", taylorOrder);
	inputData.readValue("<dimension>", dimension);
	inputData.readValue("<numberOfParticles>", numberOfParticles);
	inputData.readValue("<gravity>", gravity);
	inputData.readValue("<timeStepsForOutput>", timeStepsForOutput);

	string outputPath(project_root_path + "_output/" + simulationName + "/");

	boost::filesystem::path outputDir(outputPath);
	boost::filesystem::create_directory(outputDir);

	boost::filesystem::path MATLAB_outputDir(outputPath + "MATLAB_output/");
	boost::filesystem::create_directory(MATLAB_outputDir);

	// Input
	string particleInputFolder(inputFolder + simulationName + "/");

	SphericalParticlePtrArrayKit particleArray;

	particleArray.inputParticles(numberOfParticles, particleInputFolder);


	foreach(SphericalParticlePtr particlePtr, particleArray){
		const double m = particlePtr->getScalarProperty( MASS );
		const double r = particlePtr->getScalarProperty( MASS );

		particlePtr->setScalarProperty( MOMENT_OF_INERTIA, 2 * m * r * r / 5 );
		particlePtr->setScalarProperty( VOLUME, 4 * pi<double>() * r * r * r / 3 );
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
			particle->addBodyForce(particle->getScalarProperty(MASS) * gravity);
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

				if(particle->touches(neighbor))	// If particles are in touch
				{
					Vector3D normalForce = ForceModel::normalForceLinearDashpotForce( particle, neighbor );
					ForceModel::tangentialForceCundallStrack( particle, neighbor, normalForce, timeStep );
				}
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
