// Standard
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <iterator>
#include <algorithm>

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

	int flagCounter = 0;

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

	Vector3D gravity;

	inputData.readValue("<initialTime>", initialTime);
	inputData.readValue("<timeStep>", timeStep);
	inputData.readValue("<finalTime>", finalTime);
	inputData.readValue("<taylorOrder>", taylorOrder);
	inputData.readValue("<dimension>", dimension);
	inputData.readValue("<numberOfParticles>", numberOfParticles);
	inputData.readValue("<gravity>", gravity);

	// Input
	vector <SphericalParticlePtr> particleVector;
	particleVector.resize(numberOfParticles);

	for( int i=0 ; i<numberOfParticles ; ++i )
	{
		// Read particles from input files
		string particleInputPath = inputPath + "Particle" + _itoa(i+1, new char[100], 10) + ".txt";
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
		// Set output files
	for( int counter = 0 ; counter < numberOfParticles ; ++counter ){
		outFile[counter].resize( N_FILES_PER_PARTICLE );

		string particleOutputPath = outputPath + "particle" + _itoa(counter+1, new char[100], 10) + "/";
		outFile[counter][DATA_IDX					].open(particleOutputPath + "data.txt");
		outFile[counter][FORCE_IDX					].open(particleOutputPath + "force.txt");
		outFile[counter][TORQUE_IDX					].open(particleOutputPath + "torque.txt");
		outFile[counter][POSITION_MATRIX_IDX		].open(particleOutputPath + "position_matrix.txt");
		outFile[counter][ORIENTATION_MATRIX_IDX		].open(particleOutputPath + "orientation_matrix.txt");
		outFile[counter][POSITION_IDX				].open(particleOutputPath + "position.txt");
		outFile[counter][ORIENTATION_IDX			].open(particleOutputPath + "orientation.txt");
		outFile[counter][VELOCITY_IDX				].open(particleOutputPath + "velocity.txt");
		outFile[counter][ROTATIONAL_VELOCITY_IDX	].open(particleOutputPath + "rotational_velocity.txt");
		outFile[counter][LINEAR_MOMENTUM_IDX		].open(particleOutputPath + "linear_momentum.txt");
		outFile[counter][ANGULAR_MOMENTUM_IDX		].open(particleOutputPath + "angular_momentum.txt");
		outFile[counter][MECHANICAL_ENERGY_IDX		].open(particleOutputPath + "energy.txt");
	}

		// Create output folders for each particle
	foreach(SphericalParticlePtr particlePtr, particleVector)
	{
		string particleOutputPath = outputPath + "particle" + _itoa(particlePtr->getHandle(), new char[100], 10);
		_mkdir(particleOutputPath.c_str());
	}

	string verticalSeparator = "\n";
	string horizontalSeparator = ",";

	ofstream mainOutFile(outputPath + "output.txt");
	mainOutFile << "<nParticles> "		<< numberOfParticles	<< verticalSeparator;

	mainOutFile << "<initialTime> "		<< initialTime			<< verticalSeparator;
	mainOutFile << "<timeStep> "		<< timeStep				<< verticalSeparator;
	mainOutFile << "<finalTime> "		<< finalTime			<< verticalSeparator;

	mainOutFile << "<taylorOrder> "		<< taylorOrder			<< verticalSeparator;

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
		
	/*ofstream particleData1(outputPath + "particle1/data.txt");
	ofstream particleData2(outputPath + "particle2/data.txt");

	ofstream particleForce1(outputPath + "particle1/force.txt");
	ofstream particleForce2(outputPath + "particle2/force.txt");

	ofstream particleTorque1(outputPath + "particle1/torque.txt");
	ofstream particleTorque2(outputPath + "particle2/torque.txt");

	ofstream particlePositionMatrix1(outputPath + "particle1/position_matrix.txt");
	ofstream particlePositionMatrix2(outputPath + "particle2/position_matrix.txt");

	ofstream particleOrientationMatrix1(outputPath + "particle1/orientation_matrix.txt");
	ofstream particleOrientationMatrix2(outputPath + "particle2/orientation_matrix.txt");

	ofstream particlePosition1(outputPath + "particle1/position.txt");
	ofstream particlePosition2(outputPath + "particle2/position.txt");

	ofstream particleOrientation1(outputPath + "particle1/orientation.txt");
	ofstream particleOrientation2(outputPath + "particle2/orientation.txt");

	ofstream particleVelocity1(outputPath + "particle1/velocity.txt");
	ofstream particleVelocity2(outputPath + "particle2/velocity.txt");

	ofstream particleRotationalVelocity1(outputPath + "particle1/rotational_velocity.txt");
	ofstream particleRotationalVelocity2(outputPath + "particle2/rotational_velocity.txt");

	ofstream particleLinearMomentum1(outputPath + "particle1/linear_momentum.txt");
	ofstream particleLinearMomentum2(outputPath + "particle2/linear_momentum.txt");

	ofstream particleAngularMomentum1(outputPath + "particle1/angular_momentum.txt");
	ofstream particleAngularMomentum2(outputPath + "particle2/angular_momentum.txt");

	ofstream particleEnergy1(outputPath + "particle1/energy.txt");
	ofstream particleEnergy2(outputPath + "particle2/energy.txt");
	
	particlePositionMatrix1 << 0 << verticalSeparator;
	particlePositionMatrix2 << 0 << verticalSeparator;

	// Save particle data
	particleData1 << "<Radius> " << particlePtr1->getGeometricParameter(RADIUS) << verticalSeparator;
	particleData2 << "<Radius> " << particlePtr2->getGeometricParameter(RADIUS) << verticalSeparator;

	// Save every derivative of particles' positions
	saveSphericalParticlePosition(particlePositionMatrix1, *particlePtr1, horizontalSeparator, verticalSeparator);
	saveSphericalParticlePosition(particlePositionMatrix2, *particlePtr2, horizontalSeparator, verticalSeparator);
	
	saveSphericalParticleOrientation(particleOrientationMatrix1, *particlePtr1, horizontalSeparator, verticalSeparator);
	saveSphericalParticleOrientation(particleOrientationMatrix2, *particlePtr2, horizontalSeparator, verticalSeparator);

	saveVector3D(particleForce1, particlePtr1->getResultingForce(), horizontalSeparator);
	saveVector3D(particleForce2, particlePtr2->getResultingForce(), horizontalSeparator);
	particleForce1 << verticalSeparator;
	particleForce2 << verticalSeparator;
	
	saveVector3D(particleTorque1, particlePtr1->getResultingTorque(), horizontalSeparator);
	saveVector3D(particleTorque2, particlePtr2->getResultingTorque(), horizontalSeparator);
	particleTorque1 << verticalSeparator;
	particleTorque2 << verticalSeparator;

	saveVector3D(particlePosition1, particlePtr1->getPosition(0), horizontalSeparator);
	saveVector3D(particlePosition2, particlePtr2->getPosition(0), horizontalSeparator);
	particlePosition1 << verticalSeparator;
	particlePosition2 << verticalSeparator;

	saveVector3D(particleOrientation1, particlePtr1->getOrientation(0), horizontalSeparator);
	saveVector3D(particleOrientation2, particlePtr2->getOrientation(0), horizontalSeparator);
	particleOrientation1 << verticalSeparator;
	particleOrientation2 << verticalSeparator;

	saveVector3D(particleVelocity1, particlePtr1->getPosition(1), horizontalSeparator);
	saveVector3D(particleVelocity2, particlePtr2->getPosition(1), horizontalSeparator);
	particleVelocity1 << verticalSeparator;
	particleVelocity2 << verticalSeparator;

	saveVector3D(particleRotationalVelocity1, particlePtr1->getOrientation(1), horizontalSeparator);
	saveVector3D(particleRotationalVelocity2, particlePtr2->getOrientation(1), horizontalSeparator);
	particleRotationalVelocity1 << verticalSeparator;
	particleRotationalVelocity2 << verticalSeparator;

	saveVector3D(particleLinearMomentum1, particlePtr1->getLinearMomentum(), horizontalSeparator);
	saveVector3D(particleLinearMomentum2, particlePtr2->getLinearMomentum(), horizontalSeparator);
	particleLinearMomentum1 << verticalSeparator;
	particleLinearMomentum2 << verticalSeparator;
	
	saveVector3D(particleAngularMomentum1, particlePtr1->getAngularMomentum(), horizontalSeparator);
	saveVector3D(particleAngularMomentum2, particlePtr2->getAngularMomentum(), horizontalSeparator);
	particleAngularMomentum1 << verticalSeparator;
	particleAngularMomentum2 << verticalSeparator;

	particleEnergy1 << particlePtr1->getMechanicalEnergy() << verticalSeparator;
	particleEnergy2 << particlePtr2->getMechanicalEnergy() << verticalSeparator;
		*/
	// ===== Simulation =====
	particleVector[0]->addNeighbor( *particleVector[1] );

	bool collisionFlag = false;

	for(double t = initialTime; t <= finalTime - timeStep ; t += timeStep){

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
		/*
		foreach( SphericalParticle* particle, particleVector ){
			foreach( SphericalParticle* particle, particleVector ){

			}
		}*/

		if(particleVector[0]->touch(*particleVector[1]))	// If particles are in touch
		{
			if(collisionFlag == false){
				collisionFlag = true;
				cout << "Collision start: " << t << " s" << endl;
			}
			ForceModel::viscoelasticSpheres( *particleVector[0], *particleVector[1] );
		}
		else if(collisionFlag == true){
				collisionFlag = false;
				cout << "Collision end: " << t << " s" << endl;
		}

		// Correct position and orientation
		foreach( SphericalParticlePtr particle, particleVector ){
			ForceModel::correctPosition( *particle , taylorOrder, timeStep );
			ForceModel::correctOrientation( *particle , taylorOrder, timeStep );
		}


		// ----- Saving to file -----

		// Prints every derivative of particles' position

		foreach(SphericalParticlePtr particlePtr, particleVector){
			outFile[particlePtr->getHandle()][POSITION_MATRIX_IDX] << t + timeStep << verticalSeparator;

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
	}

	for( int i=0 ; i<numberOfParticles ; ++i ){
		for( int j=0 ; j<N_FILES_PER_PARTICLE ; ++j ){
			outFile[i][j].close();
		}
	}

	mainOutFile.close();
	
	cout << endl << "Success" << endl << endl;
}
