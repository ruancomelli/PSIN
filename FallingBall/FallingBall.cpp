// Simulation draft
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include "Vector.h"

using namespace std;


inline unsigned long factorial( unsigned n ){
	unsigned long nFactorial = 1;
	
	for( unsigned k = 1 ; k <= n ; ++k )
		nFactorial *= k;
	
	return nFactorial;
}

vector < vector <double> > taylorPredictor( vector < vector <double> > currentVector, unsigned predictionOrder, double timeStep ){
	// predictionOrder is the order of the derivatives to be computed.
	// timeStep is the time step for the predictionOrder
	// currentVector is a matrix of size predictionOrder X nDimensions, where nDimensions is the number of dimensions of the function to be predicted
	
	// This algorithm is an implementation of equation (2.24) (see reference) 
	
	vector < vector <double> > predictedVector;
	vector <double> taylorExpansion;
	
	unsigned nDimensions = currentVector[0].size();
	
	// initialize predictedVector and taylorExpansion
	taylorExpansion.resize( nDimensions );
	predictedVector.resize( predictionOrder + 1 );
	
	for( unsigned i = 0 ; i <= predictionOrder ; ++i ){
		predictedVector[i].resize( nDimensions );
	}
	
	// predict position
	for( unsigned i = 0; i <= predictionOrder; ++i ){
		
		// set each entry of taylorExpansion to zero
		for( unsigned j = 0 ; j < nDimensions ; ++j ){
			taylorExpansion[j] = 0;
		}
		
		// perform summation
		for( unsigned j = i; j <= predictionOrder; ++j ){
			taylorExpansion += ( pow( timeStep , static_cast<int>(j - i)) / factorial( j - i ) ) * currentVector[j];// * currentVector[j];
		}
		
		// set the i-th predicted derivative as the calculated Taylor expansion
		predictedVector[i] = taylorExpansion;
		
	}

	return predictedVector;
}

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
	vector < vector <double> > particlePosition;
	particlePosition.resize(3);
	for(unsigned i = 0 ; i < 3 ; ++i ){
		particlePosition[i].resize(3, 0);
	}
	
	// Output
	ofstream outFile;
	outFile.open("output.txt");
	
	// Simulation
	outFile << "Particle 1\n";
	outFile << "\tPosition\n";
	for(double t = initialTime; t <= finalTime ; t += timeStep){
		
		particlePosition[2] = gravity;
		particlePosition = taylorPredictor( particlePosition, 2, timeStep );
		
		// Saving to file
		outFile << "\t\t" << t << "\n";
		// Prints every derivative of particlePosition
		for(unsigned i = 0 ; i <= 2 ; ++i ){
			outFile << "\t\t";
			
			// Saves each component of the i-th derivative of the position
			for(unsigned j = 0 ; j < 3 ; ++j){
				outFile << "\t" << particlePosition[i][j];
			}
			
			outFile << "\n";
		}
		outFile << "\n";
	}
	
	// Test
	cout << "\nOrigin:" << endl;
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
	
	
	outFile.close();
	
	cout << endl << "Success" << endl << endl;
	system("pause");	
	
}

