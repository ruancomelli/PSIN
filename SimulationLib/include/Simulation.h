#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <algorithm>
#include "Particle.h"
#include "ForceModel.h"

using namespace std;


class Simulation
{
	public:
		// ----- Constructors -----
		Simulation(string inputFile);
		Simulation(int option);
		
		// ----- Force Model and Integration Scheme -----
		void setForceModel(const string & forceModel);
		string getForceModel(void);
		
		void setForceCalculatedQuantity(const string & calculatedQuantity);
		string getCalculatedQuantity(void);
		
		void setForceCalculation(vector <double> (*function)( const Particle &, const Particle &) );
		
		// ----- Input and Output -----
		void setInputFile(const string &);
		void setOutputFile(const string &);
		
		// ----- Simulate -----
		void simulate(void);
		
		// ----- Initialization -----
		void initializeParticle(Particle, int);
		
	private:
		vector <double> (*forceCalculation)( const Particle &, const Particle &);
		string forceModel; // "LINEAR DASHPOT FORCE"
		string forceCalculatedQuantity; // "FORCE" or "IMPULSE"
		string forceCalculationMethod; // "FINITE DIFFERENCE" or "INTEGRATION"
		
		long int numberOfParticles;
		
		string inputFile;	// Input file for parameters
		string outputFile;	// Output file for exporting data
		
	
	protected:
};


#endif


