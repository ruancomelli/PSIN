#ifndef SIMULATION_H
#define SIMULATION_H

// ===============================================
// ================= TEMPORARY: ==================
// Standard
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdio>
#include <iterator>
#include <algorithm>
#include <map>
#include <string>

// PropertyLib
#include <PropertyContainer.h>
#include <PropertyList.h>

// EntityLib
#include <Particle.h>
#include <SphericalParticle.h>

// UtilsLib
#include <FileSystem.h>
#include <Foreach.h>
#include <Mathematics.h>
#include <SharedPointer.h>
#include <Vector.h>

// ForceModelLib
#include <ForceModel.h>
#include <ForceModelList.h>
#include <ForceMethodsDefinitions.h>
#include <ForceModelSet.h>

// IOLib
#include <FileReader.h>
#include <SphericalParticlePtrArrayKit.h>

using namespace std;
using namespace PropertyList;
// ===============================================


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
// ===============================================
// ================= TEMPORARY: ==================
		void doItAll(const string project_root_path);
// ===============================================

		Simulation(const string inputFolder);

		void inputMainData(void);

		// Set files
		bool setInputFolder(const string inputFolder);
		bool setProjectRootPath(const string projectRootPath);
		bool setParticleInputFolder(const string particleInputFolder);
		bool setOutputPath(const string outputPath);

		// Name
		void setName( const string name );
		string getName( void ) const;

	private:
		// Simulation Folders and Paths
		string name;	// This should be something like "Simulation1", or "MySimulation"

		string projectRootPath;	// This should be something like C:/ParticleSimulator/
		string inputFolder;	// This should be something like project_root_path + "_input/"
		string particleInputFolder;
		string outputPath;

		// Simulation data
		double initialTime;
		double timeStep;
		double finalTime;
		int taylorOrder;
		int dimension;
		int numberOfParticles;
		int timeStepsForOutput;
		Vector3D gravity = Vector3D();

		// Simulation objects
		SphericalParticlePtrArrayKit particleArray;
		ForceModel forceModel;

		bool isReady = false;

}; // class Simulation


#endif	// SIMULATION_H


