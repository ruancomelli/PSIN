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

	// Coordinate system
	Vector3D origin;
	Vector3D xVersor(1, 0, 0);
	Vector3D yVersor(0, 1, 0);
	Vector3D zVersor(0, 0, 1);
	
	// Initialize gravity
	Vector3D gravity(0.0, 0.0, 0.0);
	
	// Simulation data
	double initialTime = 0;
	double timeStep = 0.1;
	double finalTime = 15;
	
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
	particle2.setGeometricParameter( RADIUS, .5 );

	
	// Output
	ofstream outFile1("../_output/output1.txt");
	ofstream outFile2("../_output/output2.txt");

	string verticalSeparator = "\n";
	string horizontalSeparator = ",";
	
	// Simulation
	for(double t = initialTime; t <= finalTime ; t += timeStep){

		if(particle1.touch(particle2))	// If particles are in touch
		{
			cout << "Collision Instant: " << t << endl;
		}

		particle1.setPosition(2, gravity);
		particle2.setPosition(2, gravity);

		particle1.setPosition(ForceModel::taylorPredictor( particle1.getPosition(), 2, timeStep ));
		particle2.setPosition(ForceModel::taylorPredictor( particle2.getPosition(), 2, timeStep ));


		// ----- Saving to file -----
		outFile1 << t << verticalSeparator;
		outFile2 << t << verticalSeparator;

		// Prints every derivative of particles' position
		for(unsigned i = 0 ; i <= 2 ; ++i ){
			
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
