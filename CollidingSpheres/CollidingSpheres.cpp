// Standard
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <iterator>
#include <algorithm>
#include <map>
#include <string>

// PropertyLib
#include <PropertyContainer.h>
#include <PropertyList.h>

// EntityLib
#include <Particle.h>
#include <SphericalParticle.h>

// UtilsLib
#include <Vector.h>
#include <Mathematics.h>
#include <Foreach.h>
#include <SharedPointer.h>

// ForceModelLib
#include <ForceModel.h>
#include <ForceModelList.h>
#include <ForceModelSet.h>

// IOLib
#include <FileReader.h>
#include <SphericalParticlePtrArrayKit.h>

// boost
#include <boost/math/constants/constants.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace PropertyList;

using boost::math::constants::pi;

const string project_root_path = PROJECT_PATH;

int main(int argc, char **argv){

	int defaultDimension = 3; // This means that we are constrained to Vector3D

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

	string outputPath(project_root_path + "_output/" + simulationName + "/");

	boost::filesystem::path outputDir(outputPath);
	boost::filesystem::create_directory(outputDir);

	boost::filesystem::path MATLAB_outputDir(outputPath + "MATLAB_output/");
	boost::filesystem::create_directory(MATLAB_outputDir);

	ForceModel forceModel;

	for (auto& fm : forceModelSet)
	{
		if (fm.getName() == forceModelName)
		{
			forceModel = fm;
			break;
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
