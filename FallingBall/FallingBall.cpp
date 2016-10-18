// Simulation draft
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "Vector.h"
#include "../ForceModelLib/include/ForceModel.h" // I don't know why ' #include "ForceModel.h" ' generates error!!!

using namespace std;

int main(int argc, char **argv){
//Particle particle;

	// Coordinate system
	Vector3D origin(0.0, 0.0, 0.0);
	Vector3D xVersor(1.0, 0.0, 0.0);
	Vector3D yVersor(0.0, 1.0, 0.0);
	Vector3D zVersor(0.0, 0.0, 1.0);
	
	// Initialize gravity
	Vector3D gravity(0.0, -9.81, 0.0);
	
	// Simulation data
	double initialTime = 0;
	double timeStep = 1;
	double finalTime = 100;
	
	// Initialize particle
	vector < Vector3D > particlePosition;
	particlePosition.resize(3);
	
	// Output
	ofstream outFile;
	outFile.open("output.txt");
	
	// Simulation
	outFile << "Particle 1\n";
	outFile << "\tPosition\n";
	for(double t = initialTime; t <= finalTime ; t += timeStep){
		
		particlePosition[2] = gravity;
		particlePosition = ForceModel::taylorPredictor( particlePosition, 2, timeStep );
		
		// Saving to file
		outFile << "\t\t" << t << "\n";
		// Prints every derivative of particlePosition
		for(unsigned i = 0 ; i <= 2 ; ++i ){
			outFile << "\t\t";
			
			// Saves each component of the i-th derivative of the position
			outFile << "\t" << particlePosition[i].x();
			outFile << "\t" << particlePosition[i].y();
			outFile << "\t" << particlePosition[i].z();
			
			outFile << "\n";
		}
		outFile << "\n";
	}
	
	// Test
/*	cout << "\nOrigin:" << endl;
	for( vector <double>::iterator k = origin.begin() ; k != origin.end() ; ++k)
		cout << *k << endl;
	
	cout << "\nX:" << endl;
	for( vector <double>::iterator k = xVersor.begin() ; k != xVersor.end() ; ++k)
		cout << *k << endl;
	
	cout << "\nY:" << endl;
	for( vector <double>::iterator k = yVersor.begin() ; k != yVersor.end() ; ++k)
		cout << *k << endl;
	
	cout << "\nZ:" << endl;
	for( vector <double>::iterator k = zVersor.begin() ; k != zVersor.end() ; ++k)
		cout << *k << endl;
	
	cout << "\nGravity:" << endl;
	for(unsigned i = 0; i<3; ++i){
		cout << gravity[i] << endl;
	}
*/
	
	
	outFile.close();
	
	cout << endl << "Success" << endl << endl;
/*	system("pause");	*/
	
}

