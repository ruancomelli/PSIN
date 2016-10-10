#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <Particle.h>
#include <Vector.h>
#include <ForceModel.h>

using namespace std;

int main(int argc, char **argv){

	// Coordinate system
	vector <double> origin(3,0);
	vector <double> xVersor(3,0);
	vector <double> yVersor(3,0);
	vector <double> zVersor(3,0);
	xVersor[0] = yVersor[1] = zVersor[2] = 1;
	
	// Initialize gravity
	vector <double> gravity(3,0);
	gravity[0] = 0.0;
	gravity[1] = -9.81;
	gravity[2] = 0.0;
	
	// Simulation data
	double initialTime = 0;
	double timeStep = 1;
	double finalTime = 100;
	
	// Initialize particles
	Particle particle1;
	Particle particle2;
	
	double initialPosition1[3][3] =	{
		{0.,0.,0.},
		{1.,0.,0.},
		{0.,0.,0.}
	};
	double initialPosition2[3][3] = {
		{10.,0.,0.},
		{0.,0.,0.},
		{0.,0.,0.}
	};

	particle1.setPosition(setVector2D<double>(initialPosition1[0], 3, 3));
	particle2.setPosition(setVector2D<double>(initialPosition2[0], 3, 3));
	
	
	// Output
	ofstream outFile1("output\\output1.txt");
	ofstream outFile2("output\\output2.txt");
	
	// Simulation
	for(double t = initialTime; t <= finalTime ; t += timeStep){
		
		particle1.setPosition(gravity, 2);
		particle2.setPosition(gravity, 2);
		
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
			for(unsigned j = 0 ; j < 3 ; ++j){
				outFile1 << "\t" << particle1.getPosition(i)[j];
				outFile2 << "\t" << particle2.getPosition(i)[j];
			}
			
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

