#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <Particle.h>
#include <Vector.h>
#include <setVector.h>
#include <ForceModel.h>

using namespace std;

int main(int argc, char **argv){

	// Coordinate system
	Vector3D origin;
	Vector3D xVersor(1, 0, 0);
	Vector3D yVersor(0, 1, 0);
	Vector3D zVersor(0, 0, 1);
	
	// Initialize gravity
	Vector3D gravity(0.0, -9.81, 0.0);
	
	// Simulation data
	double initialTime = 0;
	double timeStep = 1;
	double finalTime = 100;
	
	// Initialize particles
	Particle particle1;
	Particle particle2;

	particle1.setPosition(0, 0.0, 0.0, 0.0);
	particle1.setPosition(1, 1.0, 0.0, 0.0);
	particle1.setPosition(2, 0.0, 0.0, 0.0);
		
	particle2.setPosition(0, 10.0, 0.0, 0.0);
	particle2.setPosition(1, 0.0, 0.0, 0.0);
	particle2.setPosition(2, 0.0, 0.0, 0.0);
	
	
	// Output
	ofstream outFile1("../_output/output1.txt");
	ofstream outFile2("../_output/output2.txt");
	
	// Simulation
	for(double t = initialTime; t <= finalTime ; t += timeStep){
		
		particle1.setPosition(2, gravity);
		particle2.setPosition(2, gravity);
		
		particle1.setPosition(ForceModel::taylorPredictor( particle1.getPosition(), 2, timeStep ));
		particle2.setPosition(ForceModel::taylorPredictor( particle2.getPosition(), 2, timeStep ));
		
		// Saving to file
		outFile1 << t << "\n";
		outFile2 << t << "\n";

		// Prints every derivative of particles' position
		for(unsigned i = 0 ; i <= 2 ; ++i ){
			outFile1 << "\t";
			outFile2 << "\t";
			
			// Saves each component of the i-th derivative of the positions
			outFile1 << "\t" << particle1.getPosition(i).x();
			outFile2 << "\t" << particle2.getPosition(i).x();
			outFile1 << "\t" << particle1.getPosition(i).y();
			outFile2 << "\t" << particle2.getPosition(i).y();
			outFile1 << "\t" << particle1.getPosition(i).z();
			outFile2 << "\t" << particle2.getPosition(i).z();
			
			outFile1 << "\n";
			outFile2 << "\n";
		}
		outFile1 << "\n";
		outFile2 << "\n";
	}
	
	outFile1.close();
	outFile2.close();
	
	cout << endl << "Success" << endl << endl;
}

