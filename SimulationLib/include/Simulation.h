#ifndef SIMULATION_H
#define SIMULATION_H

// ForceModelLib
#include <ForceModel.h>

// IOLib
#include <SphericalParticlePtrArrayKit.h>

// UtilsLib
#include <Vector3D.h>

// Standard
#include <string>

using std::string;

class Simulation
{
	public:
		Simulation(const string inputFolder);

		void inputMainData(void);

		// Name
		void setName( const string name );
		string getName( void ) const;

	private:
		// Simulation Folders and Paths
		string inputFolder;	// This should be something like project_root_path + "_input/"
		string name;	// This should be something like "Simulation1", or "MySimulation"

		// Simulation data
		double initialTime;
		double timeStep;
		double finalTime;
		int taylorOrder;
		int dimension;
		int numberOfParticles;
		int timeStepsForOutput;
		Vector3D gravity;

		// Simulation objects
		SphericalParticlePtrArrayKit particleArray;
		ForceModel forceModel;

}; // class Simulation


#endif	// SIMULATION_H


