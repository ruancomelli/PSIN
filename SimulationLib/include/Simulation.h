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
#include <ForceMethodsDefinitions.h>

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
		struct ForceModelCompare{
			bool operator()( const ForceModel & left, const ForceModel & right ) const
			{ return left.getName() < right.getName();}
		};

// ===============================================
// ================= TEMPORARY: ==================
		void doItAll(const string project_root_path);
// ===============================================

		// Simulation(const string inputFolder);

		void inputMainData(void);

		// Set files
		bool setInputFolder(const string inputFolder);
		bool setProjectRootFolder(const string projectRootFolder);
		bool setParticleInputFolder(const string particleInputFolder);
		bool setOutputFolder(const string outputFolder);

		// Set simulation data
		

		// Name
		void readName(void);
		void setName( const string name );
		string getName(void) const;

		// ForceModel
		void addForceModel( const ForceModel & fm );

	private:
		// Simulation Folders and Paths
		string name;	// This should be something like "Simulation1", or "MySimulation"

		string projectRootFolder;	// This should be something like C:/ParticleSimulator/
		string inputFolder;	// This should be something like project_root_path + "_input/"
		string particleInputFolder;
		string outputFolder;

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
		std::set<ForceModel, Simulation::ForceModelCompare> forceModelSet;

}; // class Simulation


#endif	// SIMULATION_H


