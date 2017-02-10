#ifndef SPHERICAL_PARTICLE_PTR_ARRAY_KIT_H
#define SPHERICAL_PARTICLE_PTR_ARRAY_KIT_H

// Standard
#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

// EntityLib
#include <SphericalParticle.h>

// IOLib
#include <readSphericalParticle.h>

// UtilsLibSpecific
#include <Foreach.h>

// boost
#include <boost/filesystem.hpp>

using namespace std;

class SphericalParticlePtrArrayKit: public SphericalParticlePtrArray
{
	public:
		SphericalParticlePtrArrayKit();
		virtual ~SphericalParticlePtrArrayKit();

		void inputParticle(string & inputPath);
		void inputParticles(int nParticles, string & inputPath);
		void inputParticles(vector<string> & inputPath);

		void openFiles(string outputPath);

		void exportTemporalData(string horizontalSeparator, string verticalSeparator);
		void exportTemporalDataCSV(){ exportTemporalData(",", "\n"); }

		void exportAllData(string horizontalSeparator, string verticalSeparator);
		void exportAllDataCSV(){ exportAllData(",", "\n"); }

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

		/* These functions only make the program clearer */
		inline void saveVector3D(ofstream & outFile, Vector3D v, string horizontalSeparator, string verticalSeparator){
				outFile << 	v.x() << horizontalSeparator << 
							v.y() << horizontalSeparator << 
							v.z() << verticalSeparator;
		}

		inline void saveSphericalParticlePositionMatrix(ofstream & outFile, SphericalParticle & particle, string horizontalSeparator, string verticalSeparator){
			for(int i = 0 ; i <= particle.getTaylorOrder() ; ++i ){
				// Save each component of the i-th derivative of the positions
				outFile << horizontalSeparator;
				saveVector3D(outFile, particle.getPosition(i), horizontalSeparator, verticalSeparator);
			}
			outFile << verticalSeparator;
		}
		
		inline void saveSphericalParticleOrientationMatrix(ofstream & outFile, SphericalParticle & particle, string horizontalSeparator, string verticalSeparator){
			for(int i = 0 ; i <= particle.getTaylorOrder() ; ++i ){
				// Save each component of the i-th derivative of the orientations
				outFile << horizontalSeparator;
				saveVector3D(outFile, particle.getOrientation(i), horizontalSeparator, verticalSeparator);
			}
			outFile << verticalSeparator;
		}

}; // class SphericalParticlePtrArrayKit


#endif
