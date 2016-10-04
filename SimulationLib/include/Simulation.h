#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <algorithm>
#include "Particle.h"
#include "ForceModel.h"

using namespace std



class Simulation
{
	public:
		// ----- Force Model and Integration Scheme -----
		void setForceModel(const string ForceModel &);
		string getForceModel(void);
		
		void setForceCalculatedQuantity(const string calculatedQuantity &);
		string getCalculatedQuantity(void);
		
		void setForceCalculation(vector <double> (*function)( const Particle &, const Particle &) );
		
		void setInputFile(const string &);
		void setOutputFile(const string &);
		
		
		
	private:
		vector <double> (*forceCalculation)( const Particle &, const Particle &);
		string forceModel; // "LINEAR DASHPOT FORCE"
		string forceCalculatedQuantity; // "FORCE" or "IMPULSE"
		string forceCalculationMethod; // "FINITE DIFFERENCE" or "INTEGRATION"
		
		long unsigned numberOfParticles;
		
		string inputFile;
		string outputFile;
		
	
	protected:
};

#endif
