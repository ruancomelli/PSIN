#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <Particle.h>
#include <Vector.h>
#include <setVector.h>
#include <ForceModel.h>
#include <SphericalParticle.h>

using namespace std;

int main(int argc, char **argv){

	int defaultDimension = 3; // This means that we are constraint to Vector3D

	// Global coordinate system
	Vector3D origin(0.0, 0.0, 0.0);
	Vector3D xVersor(1.0, 0.0, 0.0);
	Vector3D yVersor(0.0, 1.0, 0.0);
	Vector3D zVersor(0.0, 0.0, 1.0);
	
	// Initialize gravity
	Vector3D gravity(0.0, 0.0, 0.0);
	
	// Simulation data
	double initialTime = 0.0;
	double timeStep = 0.1;
	double finalTime = 15.0;
	
	int taylorOrder = 2;
	int dimension = 2;

	// Initialize particles
	SphericalParticle particle1( taylorOrder, dimension, 1 );
	SphericalParticle particle2( taylorOrder, dimension, 2 );

	particle1.setPosition(0, 0.0, 0.0, 0.0);
	particle1.setPosition(1, 1.0, 0.0, 0.0);
	particle1.setPosition(2, 0.0, 0.0, 0.0);
		
	particle2.setPosition(0, 10.0, 0.0, 0.0);
	particle2.setPosition(1, 0.0, 0.0, 0.0);
	particle2.setPosition(2, 0.0, 0.0, 0.0);

	particle1.setGeometricParameter( RADIUS, 1 );
	particle2.setGeometricParameter( RADIUS, 0.5 );

	particle1.setScalarProperty(MASS, 100.0);
	particle2.setScalarProperty(MASS, 10.0);

	
	// Output
	string verticalSeparator = "\n";
	string horizontalSeparator = ",";

	ofstream mainOutFile("../_output/output.txt");
	mainOutFile << "Number of Particles =" << 2 << verticalSeparator;
	mainOutFile << "Particle1: Radius ="<< particle1.getGeometricParameter(RADIUS) << verticalSeparator;
	mainOutFile << "Particle2: Radius ="<< particle2.getGeometricParameter(RADIUS) << verticalSeparator;

	ofstream outFile1("../_output/output1.txt");
	ofstream outFile2("../_output/output2.txt");

	
	// Simulation
	for(double t = initialTime; t <= finalTime ; t += timeStep){

		// Set forces to zero
		particle1.setResultingForce(nullVector3D());
		particle2.setResultingForce(nullVector3D());

		// Body forces
		particle1.addForce(particle1.getScalarProperty(MASS) * gravity);
		particle2.addForce(particle2.getScalarProperty(MASS) * gravity);

		// Contact forces
		if(particle1.touch(particle2))	// If particles are in touch
		{
			cout << "Collision Instant: " << t << endl;
		}

		particle1.setPosition(ForceModel::taylorPredictor( particle1.getPosition(), 2, timeStep ));
		particle2.setPosition(ForceModel::taylorPredictor( particle2.getPosition(), 2, timeStep ));


		// ----- Saving to file -----
		outFile1 << t << verticalSeparator;
		outFile2 << t << verticalSeparator;

		// Prints every derivative of particles' position
		for(int i = 0 ; i <= 2 ; ++i ){
			
			// Saves each component of the i-th derivative of the positions
			outFile1 << horizontalSeparator << particle1.getPosition(i).x();
			outFile2 << horizontalSeparator << particle2.getPosition(i).x();
			outFile1 << horizontalSeparator << particle1.getPosition(i).y();
			outFile2 << horizontalSeparator << particle2.getPosition(i).y();
			outFile1 << horizontalSeparator << particle1.getPosition(i).z();
			outFile2 << horizontalSeparator << particle2.getPosition(i).z();
			
			outFile1 << verticalSeparator;
			outFile2 << verticalSeparator;
		}
		outFile1 << verticalSeparator;
		outFile2 << verticalSeparator;
	}
	
	outFile1.close();
	outFile2.close();
	
	cout << endl << "Success" << endl << endl;
}
