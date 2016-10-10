// Simulation draft
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "Particle.h"
#include "Vector.h"
#include "ForceModel.h"
//#include "../ForceModelLib/include/ForceModel.h" // I don't know why ' #include "ForceModel.h" ' generates error!!!

using namespace std;

int main(int argc, char **argv){
//Particle particle;

	// Coordinate system
	vector <double> origin(3,0);
	vector <double> xVersor(3,0);
	vector <double> yVersor(3,0);
	vector <double> zVersor(3,0);
	xVersor[0] = yVersor[1] = zVersor[2] = 1;
	
	// Initialize gravity
	vector <double> gravity;
	gravity.resize(3);
	double G[3] = {0, -9.81, 0};
	for(unsigned i = 0; i<3; ++i){
		gravity[i] = G[i];
	}
	
	// Simulation data
	double initialTime = 0;
	double timeStep = 1;
	double finalTime = 100;
	
	// Initialize particle
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
	ofstream outFile;
	outFile.open("output/output.txt");
	
	// Simulation
	for(double t = initialTime; t <= finalTime ; t += timeStep){
		
		particle1.setPosition(gravity, 2);
		particle2.setPosition(gravity, 2);
		
		particle1.setPosition(ForceModel::taylorPredictor( particle1.getPosition(), 2, timeStep ));
		particle2.setPosition(ForceModel::taylorPredictor( particle2.getPosition(), 2, timeStep ));
		
		outFile << "Particle 1 \n";
		// Saving to file
		outFile << "\t" << t << "\n";
		// Prints every derivative of particlePosition
		for(unsigned i = 0 ; i <= 2 ; ++i ){
			outFile << "\t\t";
			
			// Saves each component of the i-th derivative of the position
			for(unsigned j = 0 ; j < 3 ; ++j){
				//outFile << "\t" << particlePosition[i][j];
			}
			
			outFile << "\n";
		}
		outFile << "\n";
	}
	
	
	outFile.close();
	
	cout << endl << "Success" << endl << endl;
	system("pause");	
	
}

