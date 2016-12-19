// Standard
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <iterator>
#include <algorithm>
#include <map>

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

// IOLib
#include <readEntity.h>
#include <readPhysicalEntity.h>
#include <readParticle.h>
#include <readSphericalParticle.h>
#include <FileReader.h>

// boost
#include <boost/math/constants/constants.hpp>

// System
#include <direct.h>

using namespace std;

using boost::math::constants::pi;

inline void saveVector3D(ofstream & outFile, Vector3D v, string horizontalSeparator, string verticalSeparator){
		outFile << v.x() << horizontalSeparator << v.y() << horizontalSeparator << v.z();
		outFile << verticalSeparator;
}

inline void saveSphericalParticlePosition(ofstream & outFile, SphericalParticle & particle, string horizontalSeparator, string verticalSeparator){
	for(int i = 0 ; i <= particle.getTaylorOrder() ; ++i ){
		// Save each component of the i-th derivative of the positions
		outFile << horizontalSeparator;
		saveVector3D(outFile, particle.getPosition(i), horizontalSeparator, verticalSeparator);
	}
	outFile << verticalSeparator;
}
inline void saveSphericalParticleOrientation(ofstream & outFile, SphericalParticle & particle, string horizontalSeparator, string verticalSeparator){
	for(int i = 0 ; i <= particle.getTaylorOrder() ; ++i ){
		// Save each component of the i-th derivative of the orientations
		outFile << horizontalSeparator;
		saveVector3D(outFile, particle.getOrientation(i), horizontalSeparator, verticalSeparator);
	}
	outFile << verticalSeparator;
}


int main(int argc, char **argv){

	int defaultDimension = 3; // This means that we are constraint to Vector3D
	string inputPath("../_input/");
	string outputPath("../_output/");
	
	// Simulation data
	FileReader inputData(inputPath + "input.txt");
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

	// Input
	vector <SphericalParticlePtr> particleVector;
	particleVector.resize(numberOfParticles);

	for( int i=0 ; i<numberOfParticles ; ++i )
	{
		// Read particles from input files
		string particleInputPath = inputPath + "particle" + _itoa(i, new char[100], 10) + ".txt";
		particleVector[i] = readSphericalParticle(particleInputPath);
		particleVector[i]->setHandle(i);
	}

	foreach(SphericalParticlePtr particlePtr, particleVector){
		double m = particlePtr->getScalarProperty( MASS );
		double r = particlePtr->getScalarProperty( MASS );

		particlePtr->setScalarProperty( MOMENT_OF_INERTIA, 2 * m * r * r / 5 );
		particlePtr->setScalarProperty( VOLUME, 4 * pi<double>() * r * r * r / 3 );
	}

	particleVector[0]->setGravity(gravity);
	
	// Output
	
	enum{
	 DATA_IDX = 0,
	 FORCE_IDX,
	 TORQUE_IDX,
	 POSITION_MATRIX_IDX,
	 ORIENTATION_MATRIX_IDX,
	 POSITION_IDX,
	 ORIENTATION_IDX,
	 VELOCITY_IDX,
	 ROTATIONAL_VELOCITY_IDX,
	 LINEAR_MOMENTUM_IDX,
	 ANGULAR_MOMENTUM_IDX,
	 MECHANICAL_ENERGY_IDX,

	 N_FILES_PER_PARTICLE
	};
	
	vector< vector< ofstream > > outFile;
	outFile.resize(numberOfParticles);

		// Create output folders for each particle and set output files
	foreach(SphericalParticlePtr particlePtr, particleVector)
	{
		string particleOutputPath = outputPath + "Particle" + _itoa(particlePtr->getHandle(), new char[100], 10);
		_mkdir(particleOutputPath.c_str());

		outFile[particlePtr->getHandle()].resize( N_FILES_PER_PARTICLE );

		particleOutputPath = outputPath + "Particle" + _itoa(particlePtr->getHandle(), new char[100], 10) + "/";

		outFile[particlePtr->getHandle()][DATA_IDX					].open(particleOutputPath + "data.txt");
		outFile[particlePtr->getHandle()][FORCE_IDX					].open(particleOutputPath + "force.txt");
		outFile[particlePtr->getHandle()][TORQUE_IDX				].open(particleOutputPath + "torque.txt");
		outFile[particlePtr->getHandle()][POSITION_MATRIX_IDX		].open(particleOutputPath + "position_matrix.txt");
		outFile[particlePtr->getHandle()][ORIENTATION_MATRIX_IDX	].open(particleOutputPath + "orientation_matrix.txt");
		outFile[particlePtr->getHandle()][POSITION_IDX				].open(particleOutputPath + "position.txt");
		outFile[particlePtr->getHandle()][ORIENTATION_IDX			].open(particleOutputPath + "orientation.txt");
		outFile[particlePtr->getHandle()][VELOCITY_IDX				].open(particleOutputPath + "velocity.txt");
		outFile[particlePtr->getHandle()][ROTATIONAL_VELOCITY_IDX	].open(particleOutputPath + "rotational_velocity.txt");
		outFile[particlePtr->getHandle()][LINEAR_MOMENTUM_IDX		].open(particleOutputPath + "linear_momentum.txt");
		outFile[particlePtr->getHandle()][ANGULAR_MOMENTUM_IDX		].open(particleOutputPath + "angular_momentum.txt");
		outFile[particlePtr->getHandle()][MECHANICAL_ENERGY_IDX		].open(particleOutputPath + "energy.txt");
	}

	string verticalSeparator = "\n";
	string horizontalSeparator = ",";

	ofstream mainOutFile(outputPath + "output.txt");
	mainOutFile << "<nParticles> "		<< numberOfParticles	<< verticalSeparator;

	mainOutFile << "<initialTime> "		<< initialTime			<< verticalSeparator;
	mainOutFile << "<timeStep> "		<< timeStep				<< verticalSeparator;
	mainOutFile << "<finalTime> "		<< finalTime			<< verticalSeparator;

	mainOutFile << "<taylorOrder> "		<< taylorOrder			<< verticalSeparator;

	mainOutFile << "<timeStepsForOutput> "	<< timeStepsForOutput		<< verticalSeparator;

	foreach(SphericalParticlePtr particlePtr, particleVector){
		outFile[particlePtr->getHandle()][DATA_IDX] << "<Radius> " << particlePtr->getGeometricParameter(RADIUS) << verticalSeparator;

		saveSphericalParticlePosition(outFile[particlePtr->getHandle()][POSITION_MATRIX_IDX],
			*particlePtr, horizontalSeparator, verticalSeparator);

		saveSphericalParticleOrientation(outFile[particlePtr->getHandle()][ORIENTATION_MATRIX_IDX],
			*particlePtr, horizontalSeparator, verticalSeparator);
		
		saveVector3D(outFile[particlePtr->getHandle()][FORCE_IDX],
			particlePtr->getResultingForce(), horizontalSeparator, verticalSeparator);

		saveVector3D(outFile[particlePtr->getHandle()][TORQUE_IDX],
			particlePtr->getResultingTorque(), horizontalSeparator, verticalSeparator);
		
		saveVector3D(outFile[particlePtr->getHandle()][POSITION_IDX],
			particlePtr->getPosition(0), horizontalSeparator, verticalSeparator);
		
		saveVector3D(outFile[particlePtr->getHandle()][ORIENTATION_IDX],
			particlePtr->getOrientation(0), horizontalSeparator, verticalSeparator);
		
		saveVector3D(outFile[particlePtr->getHandle()][VELOCITY_IDX],
			particlePtr->getPosition(1), horizontalSeparator, verticalSeparator);
		
		saveVector3D(outFile[particlePtr->getHandle()][ROTATIONAL_VELOCITY_IDX],
			particlePtr->getOrientation(1), horizontalSeparator, verticalSeparator);
		
		saveVector3D(outFile[particlePtr->getHandle()][LINEAR_MOMENTUM_IDX],
			particlePtr->getLinearMomentum(), horizontalSeparator, verticalSeparator);
		
		saveVector3D(outFile[particlePtr->getHandle()][ANGULAR_MOMENTUM_IDX],
			particlePtr->getAngularMomentum(), horizontalSeparator, verticalSeparator);
		
		outFile[particlePtr->getHandle()][MECHANICAL_ENERGY_IDX] << particlePtr->getMechanicalEnergy() << verticalSeparator;
	}

	// ===== Simulation =====
	foreach( SphericalParticlePtr particle, particleVector ){
		foreach( SphericalParticlePtr neighbor, particleVector ){
			if( neighbor->getHandle() > particle->getHandle() ){
				particle->addNeighbor( neighbor->getHandle() );
			}
		}
	}

	int timeStepsForOutputCounter = 0;

	for(double t = initialTime; t <= finalTime ; t += timeStep){

		// Set forces and torques to zero
		foreach( SphericalParticlePtr particle, particleVector ){
			particle->setContactForce( nullVector3D() );
			particle->setBodyForce( nullVector3D() );

			particle->setResultingTorque( nullVector3D() );
		}

		// Body forces
		foreach( SphericalParticlePtr particle, particleVector ){
			particle->addBodyForce(particle->getScalarProperty(MASS) * gravity);
		}

		// Predict position and orientation
		foreach( SphericalParticlePtr particle, particleVector ){
			particle->setPosition( ForceModel::taylorPredictor( particle->getPosition(), taylorOrder, timeStep ) );
			particle->setOrientation( ForceModel::taylorPredictor( particle->getOrientation(), taylorOrder, timeStep ) );
		}

		// Contact forces
		
		foreach( SphericalParticlePtr particle, particleVector ){
			foreach( int handle, particle->getNeighborhood() ){
				SphericalParticlePtr neighbor = particleVector[handle];

				if(particle->touches(*neighbor))	// If particles are in touch
				{
					ForceModel::viscoelasticSpheres( *particle, *neighbor );
				}
			}
		}

		// Correct position and orientation
		foreach( SphericalParticlePtr particle, particleVector ){
			ForceModel::correctPosition( *particle , taylorOrder, timeStep );
			ForceModel::correctOrientation( *particle , taylorOrder, timeStep );
		}


		// ----- Saving to file -----

		// Prints every derivative of particles' position
		if( (++timeStepsForOutputCounter) == timeStepsForOutput){
			timeStepsForOutputCounter = 0;

			foreach(SphericalParticlePtr particlePtr, particleVector){
				outFile[particlePtr->getHandle()][POSITION_MATRIX_IDX] << t << verticalSeparator;
				outFile[particlePtr->getHandle()][ORIENTATION_MATRIX_IDX] << t << verticalSeparator;

				saveSphericalParticlePosition(outFile[particlePtr->getHandle()][POSITION_MATRIX_IDX],
					*particlePtr, horizontalSeparator, verticalSeparator);

				saveSphericalParticleOrientation(outFile[particlePtr->getHandle()][ORIENTATION_MATRIX_IDX],
					*particlePtr, horizontalSeparator, verticalSeparator);
		
				saveVector3D(outFile[particlePtr->getHandle()][FORCE_IDX],
					particlePtr->getResultingForce(), horizontalSeparator, verticalSeparator);

				saveVector3D(outFile[particlePtr->getHandle()][TORQUE_IDX],
					particlePtr->getResultingTorque(), horizontalSeparator, verticalSeparator);
		
				saveVector3D(outFile[particlePtr->getHandle()][POSITION_IDX],
					particlePtr->getPosition(0), horizontalSeparator, verticalSeparator);
		
				saveVector3D(outFile[particlePtr->getHandle()][ORIENTATION_IDX],
					particlePtr->getOrientation(0), horizontalSeparator, verticalSeparator);
		
				saveVector3D(outFile[particlePtr->getHandle()][VELOCITY_IDX],
					particlePtr->getPosition(1), horizontalSeparator, verticalSeparator);
		
				saveVector3D(outFile[particlePtr->getHandle()][ROTATIONAL_VELOCITY_IDX],
					particlePtr->getOrientation(1), horizontalSeparator, verticalSeparator);
		
				saveVector3D(outFile[particlePtr->getHandle()][LINEAR_MOMENTUM_IDX],
					particlePtr->getLinearMomentum(), horizontalSeparator, verticalSeparator);
		
				saveVector3D(outFile[particlePtr->getHandle()][ANGULAR_MOMENTUM_IDX],
					particlePtr->getAngularMomentum(), horizontalSeparator, verticalSeparator);
		
				outFile[particlePtr->getHandle()][MECHANICAL_ENERGY_IDX] << particlePtr->getMechanicalEnergy() << verticalSeparator;
			}
		}
	}

	for( int i=0 ; i<numberOfParticles ; ++i ){
		for( int j=0 ; j<N_FILES_PER_PARTICLE ; ++j ){
			outFile[i][j].close();
		}
	}

	mainOutFile.close();
	
	cout << endl << "Success" << endl << endl;
}
