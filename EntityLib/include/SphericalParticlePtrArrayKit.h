#ifndef SPHERICAL_PARTICLE_PTR_ARRAY_KIT_H
#define SPHERICAL_PARTICLE_PTR_ARRAY_KIT_H

// Standard
#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>
#include <string>

// EntityLib
#include <SphericalParticle.h>

using namespace std;

class SphericalParticlePtrArrayKit: public SphericalParticlePtrArray
{
	public:
		SphericalParticlePtrArrayKit();
		virtual ~SphericalParticlePtrArrayKit();

		bool inputParticles(nParticles, inputPath);
		bool openFiles(string outputPath);

		void exportToFileAsCSV();
		void exportToFile(string horizontalSeparator, string verticalSeparator);

	private:
		enum{
		 DATA_IDX = 0,
		 FORCE_IDX,
		 TORQUE_IDX,
		 POSITION_MATRIX_IDX,
		 ORIENTATION_MATRIX_IDX,
		 POSITION_IDX,
		 ORIENTATION_IDX,
		 VELOCITY_IDX,
		 ROTATIONAL_VELOCITY_IDX,
		 LINEAR_MOMENTUM_IDX,
		 ANGULAR_MOMENTUM_IDX,
		 MECHANICAL_ENERGY_IDX,

		 N_FILES_PER_PARTICLE
		};

		bool isReady;
		vector< vector< SharedPointer<ofstream> > > outFile;

}; // class SphericalParticlePtrArrayKit


#endif
