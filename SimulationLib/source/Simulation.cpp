#include "Simulation.h"

// Constructor
Simulation::Simulation(string inputFile)
{
	/*
	Write this:
	
	- Get force model, integration scheme, etc.
	- 
	*/
}

Simulation::Simulation(unsigned option){
	// For now, sending an option is the only simple way I know of initializing this
	
	switch(option){
		case 1:
			
			break;
		default:
			break;
	}
}

// Destructor
Simulation::~Simulation()
{
}

void Simulation::setForceModel(const string ForceModel &forceModelInput){
	forceModel = forceModelInput;
	transform(forceModel.begin(), forceModel.end(), forceModel.begin(), toupper);
	
	if(){
		/* Finish this */
	}
}

// Delete this: (it only exists so that I don't need to swap tabs to know the functions prototypes)
/*
		void setForceModel(const string ForceModel &);
		string getForceModel(void);
		
		void setCalculatedQuantity(const string calculatedQuantity &);
		string getCalculatedQuantity(void);
		
		void setForceCalculation(vector <double> (*function)( const Particle &, const Particle &) );
		
		void setInputFile(const string &);
		void setOutputFile(const string &);
		
		
		
	private:
		vector <double> (*forceCalculation)( const Particle &, const Particle &);
		string forceModel; // "LINEAR DASHPOT FORCE"
		string calculatedQuantity; // "FORCE" or "IMPULSE"
		
		long unsigned numberOfParticles;
		
		string inputFile;
		string outputFile;
*/