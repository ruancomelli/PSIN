// Standard
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdio>

// EntityLib
#include <Particle.h>
#include <SphericalParticle.h>

// UtilsLib
#include <Vector.h>
#include <setVector.h>
#include <Mathematics.h>
#include <Foreach.h>

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

using namespace std;

using boost::math::constants::pi;

inline void saveVector3D(ofstream & outFile, Vector3D v, string horizontalSeparator){
		outFile << v.x() << horizontalSeparator << v.y() << horizontalSeparator << v.z();
}

inline void saveSphericalParticlePosition(ofstream & outFile, SphericalParticle & particle, string horizontalSeparator, string verticalSeparator){
	for(int i = 0 ; i <= particle.getTaylorOrder() ; ++i ){
		// Save each component of the i-th derivative of the positions
		outFile << horizontalSeparator;
		saveVector3D(outFile, particle.getPosition(i), horizontalSeparator);
		outFile << verticalSeparator;
	}
	outFile << verticalSeparator;
}
inline void saveSphericalParticleOrientation(ofstream & outFile, SphericalParticle & particle, string horizontalSeparator, string verticalSeparator){
	for(int i = 0 ; i <= particle.getTaylorOrder() ; ++i ){
		// Save each component of the i-th derivative of the orientations
		outFile << horizontalSeparator;
		saveVector3D(outFile, particle.getOrientation(i), horizontalSeparator);
		outFile << verticalSeparator;
	}
	outFile << verticalSeparator;
}


int main(int argc, char **argv){

	int defaultDimension = 3; // This means that we are constraint to Vector3D
	string inputPath("../_input/");
	string outputPath("../_output/");
	
	// Initialize gravity
	
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
	SphericalParticle particle1 = readSphericalParticle(inputPath + "particle1.txt");
	SphericalParticle particle2 = readSphericalParticle(inputPath + "particle2.txt");

	particle1.setHandle(1);
	particle2.setHandle(2);

	double m1 = particle1.getScalarProperty( MASS );
	double m2 = particle2.getScalarProperty( MASS );

	double r1 = particle1.getGeometricParameter( RADIUS );
	double r2 = particle2.getGeometricParameter( RADIUS );

	particle1.setScalarProperty( MOMENT_OF_INERTIA, 2 * m1 * r1*r1 / 5 );
	particle2.setScalarProperty( MOMENT_OF_INERTIA, 2 * m2 * r2*r2 / 5 );

	particle1.setScalarProperty( VOLUME, 4 * pi<double>() * r1*r1*r1 / 3 );
	particle2.setScalarProperty( VOLUME, 4 * pi<double>() * r2*r2*r2 / 3 );

	vector <SphericalParticle*> particleVector;
	particleVector.resize(2);
	particleVector[0] = &particle1;
	particleVector[1] = &particle2;

	particle1.setGravity(gravity);
	
	// Output
	string verticalSeparator = "\n";
	string horizontalSeparator = ",";

	ofstream mainOutFile(outputPath + "output.txt");
	mainOutFile << "<nParticles> "		<< numberOfParticles	<< verticalSeparator;

	mainOutFile << "<initialTime> "		<< initialTime			<< verticalSeparator;
	mainOutFile << "<timeStep> "		<< timeStep				<< verticalSeparator;
	mainOutFile << "<finalTime> "		<< finalTime			<< verticalSeparator;

	mainOutFile << "<taylorOrder> "		<< taylorOrder			<< verticalSeparator;

	ofstream particleData1(outputPath + "Particle1/data.txt");
	ofstream particleData2(outputPath + "Particle2/data.txt");

	ofstream particleForce1(outputPath + "Particle1/force.txt");
	ofstream particleForce2(outputPath + "Particle2/force.txt");

	ofstream particleTorque1(outputPath + "Particle1/torque.txt");
	ofstream particleTorque2(outputPath + "Particle2/torque.txt");

	ofstream particlePositionMatrix1(outputPath + "Particle1/position_matrix.txt");
	ofstream particlePositionMatrix2(outputPath + "Particle2/position_matrix.txt");

	ofstream particleOrientationMatrix1(outputPath + "Particle1/orientation_matrix.txt");
	ofstream particleOrientationMatrix2(outputPath + "Particle2/orientation_matrix.txt");

	ofstream particlePosition1(outputPath + "Particle1/position.txt");
	ofstream particlePosition2(outputPath + "Particle2/position.txt");

	ofstream particleOrientation1(outputPath + "Particle1/orientation.txt");
	ofstream particleOrientation2(outputPath + "Particle2/orientation.txt");

	ofstream particleVelocity1(outputPath + "Particle1/velocity.txt");
	ofstream particleVelocity2(outputPath + "Particle2/velocity.txt");

	ofstream particleRotationalVelocity1(outputPath + "Particle1/rotational_velocity.txt");
	ofstream particleRotationalVelocity2(outputPath + "Particle2/rotational_velocity.txt");

	ofstream particleLinearMomentum1(outputPath + "Particle1/linear_momentum.txt");
	ofstream particleLinearMomentum2(outputPath + "Particle2/linear_momentum.txt");

	ofstream particleAngularMomentum1(outputPath + "Particle1/angular_momentum.txt");
	ofstream particleAngularMomentum2(outputPath + "Particle2/angular_momentum.txt");

	ofstream particleEnergy1(outputPath + "Particle1/energy.txt");
	ofstream particleEnergy2(outputPath + "Particle2/energy.txt");
	
	particlePositionMatrix1 << 0 << verticalSeparator;
	particlePositionMatrix2 << 0 << verticalSeparator;

	// Save particle data
	particleData1 << "<Radius> " << particle1.getGeometricParameter(RADIUS) << verticalSeparator;
	particleData2 << "<Radius> " << particle2.getGeometricParameter(RADIUS) << verticalSeparator;

	// Save every derivative of particles' positions
	saveSphericalParticlePosition(particlePositionMatrix1, particle1, horizontalSeparator, verticalSeparator);
	saveSphericalParticlePosition(particlePositionMatrix2, particle2, horizontalSeparator, verticalSeparator);
	
	saveSphericalParticleOrientation(particleOrientationMatrix1, particle1, horizontalSeparator, verticalSeparator);
	saveSphericalParticleOrientation(particleOrientationMatrix2, particle2, horizontalSeparator, verticalSeparator);

	saveVector3D(particleForce1, particle1.getResultingForce(), horizontalSeparator);
	saveVector3D(particleForce2, particle2.getResultingForce(), horizontalSeparator);
	particleForce1 << verticalSeparator;
	particleForce2 << verticalSeparator;
	
	saveVector3D(particleTorque1, particle1.getResultingTorque(), horizontalSeparator);
	saveVector3D(particleTorque2, particle2.getResultingTorque(), horizontalSeparator);
	particleTorque1 << verticalSeparator;
	particleTorque2 << verticalSeparator;

	saveVector3D(particlePosition1, particle1.getPosition(0), horizontalSeparator);
	saveVector3D(particlePosition2, particle2.getPosition(0), horizontalSeparator);
	particlePosition1 << verticalSeparator;
	particlePosition2 << verticalSeparator;

	saveVector3D(particleOrientation1, particle1.getOrientation(0), horizontalSeparator);
	saveVector3D(particleOrientation2, particle2.getOrientation(0), horizontalSeparator);
	particleOrientation1 << verticalSeparator;
	particleOrientation2 << verticalSeparator;

	saveVector3D(particleVelocity1, particle1.getPosition(1), horizontalSeparator);
	saveVector3D(particleVelocity2, particle2.getPosition(1), horizontalSeparator);
	particleVelocity1 << verticalSeparator;
	particleVelocity2 << verticalSeparator;

	saveVector3D(particleRotationalVelocity1, particle1.getOrientation(1), horizontalSeparator);
	saveVector3D(particleRotationalVelocity2, particle2.getOrientation(1), horizontalSeparator);
	particleRotationalVelocity1 << verticalSeparator;
	particleRotationalVelocity2 << verticalSeparator;

	saveVector3D(particleLinearMomentum1, particle1.getLinearMomentum(), horizontalSeparator);
	saveVector3D(particleLinearMomentum2, particle2.getLinearMomentum(), horizontalSeparator);
	particleLinearMomentum1 << verticalSeparator;
	particleLinearMomentum2 << verticalSeparator;
	
	saveVector3D(particleAngularMomentum1, particle1.getAngularMomentum(), horizontalSeparator);
	saveVector3D(particleAngularMomentum2, particle2.getAngularMomentum(), horizontalSeparator);
	particleAngularMomentum1 << verticalSeparator;
	particleAngularMomentum2 << verticalSeparator;

	particleEnergy1 << particle1.getMechanicalEnergy() << verticalSeparator;
	particleEnergy2 << particle2.getMechanicalEnergy() << verticalSeparator;
		
	// ===== Simulation =====
	particle1.addNeighbor( particle2 );

	for(double t = initialTime; t <= finalTime - timeStep ; t += timeStep){

		// Set forces and torques to zero
		foreach( SphericalParticle* particle, particleVector ){
			particle->setContactForce( nullVector3D() );
			particle->setBodyForce( nullVector3D() );

			particle->setResultingTorque( nullVector3D() );
		}

		// Body forces
		foreach( SphericalParticle* particle, particleVector ){
			particle->addBodyForce(particle->getScalarProperty(MASS) * gravity);
		}

		// Predict position and orientation
		foreach( SphericalParticle* particle, particleVector ){
			particle->setPosition( ForceModel::taylorPredictor( particle->getPosition(), taylorOrder, timeStep ) );
			particle->setOrientation( ForceModel::taylorPredictor( particle->getOrientation(), taylorOrder, timeStep ) );
		}

		// Contact forces
		/*
		foreach( SphericalParticle* particle, particleVector ){
			foreach( SphericalParticle* particle, particleVector ){

			}
		}*/

		if(particle1.touch(particle2))	// If particles are in touch
		{
			//cout << "Collision Instant: " << t << endl;
			ForceModel::viscoelasticSpheres( particle1, particle2 );
		}

		// Correct position and orientation
		foreach( SphericalParticle* particle, particleVector ){
			ForceModel::correctPosition( *particle , taylorOrder, timeStep );
			ForceModel::correctOrientation( *particle , taylorOrder, timeStep );
		}


		// ----- Saving to file -----

		particlePositionMatrix1 << t + timeStep << verticalSeparator;
		particlePositionMatrix2 << t + timeStep << verticalSeparator;

		// Prints every derivative of particles' position
		saveSphericalParticlePosition(particlePositionMatrix1, particle1, horizontalSeparator, verticalSeparator);
		saveSphericalParticlePosition(particlePositionMatrix2, particle2, horizontalSeparator, verticalSeparator);
		
		saveSphericalParticleOrientation(particleOrientationMatrix1, particle1, horizontalSeparator, verticalSeparator);
		saveSphericalParticleOrientation(particleOrientationMatrix2, particle2, horizontalSeparator, verticalSeparator);

		saveVector3D(particleForce1, particle1.getResultingForce(), horizontalSeparator);
		saveVector3D(particleForce2, particle2.getResultingForce(), horizontalSeparator);
		particleForce1 << verticalSeparator;
		particleForce2 << verticalSeparator;
		
		saveVector3D(particleTorque1, particle1.getResultingTorque(), horizontalSeparator);
		saveVector3D(particleTorque2, particle2.getResultingTorque(), horizontalSeparator);
		particleTorque1 << verticalSeparator;
		particleTorque2 << verticalSeparator;

		saveVector3D(particlePosition1, particle1.getPosition(0), horizontalSeparator);
		saveVector3D(particlePosition2, particle2.getPosition(0), horizontalSeparator);
		particlePosition1 << verticalSeparator;
		particlePosition2 << verticalSeparator;

		saveVector3D(particleOrientation1, particle1.getOrientation(0), horizontalSeparator);
		saveVector3D(particleOrientation2, particle2.getOrientation(0), horizontalSeparator);
		particleOrientation1 << verticalSeparator;
		particleOrientation2 << verticalSeparator;

		saveVector3D(particleVelocity1, particle1.getPosition(1), horizontalSeparator);
		saveVector3D(particleVelocity2, particle2.getPosition(1), horizontalSeparator);
		particleVelocity1 << verticalSeparator;
		particleVelocity2 << verticalSeparator;

		saveVector3D(particleRotationalVelocity1, particle1.getOrientation(1), horizontalSeparator);
		saveVector3D(particleRotationalVelocity2, particle2.getOrientation(1), horizontalSeparator);
		particleRotationalVelocity1 << verticalSeparator;
		particleRotationalVelocity2 << verticalSeparator;

		saveVector3D(particleLinearMomentum1, particle1.getLinearMomentum(), horizontalSeparator);
		saveVector3D(particleLinearMomentum2, particle2.getLinearMomentum(), horizontalSeparator);
		particleLinearMomentum1 << verticalSeparator;
		particleLinearMomentum2 << verticalSeparator;
		
		saveVector3D(particleAngularMomentum1, particle1.getAngularMomentum(), horizontalSeparator);
		saveVector3D(particleAngularMomentum2, particle2.getAngularMomentum(), horizontalSeparator);
		particleAngularMomentum1 << verticalSeparator;
		particleAngularMomentum2 << verticalSeparator;

		particleEnergy1 << particle1.getMechanicalEnergy() << verticalSeparator;
		particleEnergy2 << particle2.getMechanicalEnergy() << verticalSeparator;
	}

	particleData1.close();
	particleData2.close();
	
	particlePositionMatrix1.close();
	particlePositionMatrix2.close();

	particleOrientationMatrix1.close();
	particleOrientationMatrix2.close();

	particlePosition1.close();
	particlePosition2.close();

	particleOrientation1.close();
	particleOrientation2.close();

	particleLinearMomentum1.close();
	particleLinearMomentum2.close();

	particleAngularMomentum1.close();
	particleAngularMomentum2.close();

	particleVelocity1.close();
	particleVelocity2.close();

	particleRotationalVelocity1.close();
	particleRotationalVelocity2.close();

	particleEnergy1.close();
	particleEnergy2.close();

	mainOutFile.close();
	
	cout << endl << "Success" << endl << endl;
}
