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

Simulation::Simulation(int option){
	// For now, sending an option is the only simple way I know of initializing this
	
	switch(option){
		case 1:
				// -- Finish this!!!
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
}	// Finished

// Initialize Particle
void Simulation::initializeParticle(Particle particleVector, int option){
	switch(option){
		case 1:
			particleVector.reserve(2);
			DoubleVector2D position(taylorOrder);
			double positionMatrixForParticle1 = {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}};
			double positionMatrixForParticle2 = {{10,0,0}, {-1,0,0}, {0,0,0}, {0,0,0}};
			
			
			break;
		default:
			break;
	}
}

// Simulate
void Simulation::simulate(void){
	vector <Particle> particleVector;
	initializeParticle(particleVector, 1); // Initializes particles according to 
	
	while( continueCondition(/*FIND_PARAMETERS*/) ){
		
	}
}