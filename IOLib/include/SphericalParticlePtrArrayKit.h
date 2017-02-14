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

		void inputParticle(const string & inputPath);
		void inputParticles(const int nParticles, const string & inputPath);
		void inputParticles(const vector<string> & inputPath);

		void openFiles(const string & outputPath);

		void exportTemporalData(const string & horizontalSeparator, const string & verticalSeparator) const;
		void exportTemporalDataCSV() const { exportTemporalData(",", "\n"); }

		void exportAllData(const string & horizontalSeparator, const string & verticalSeparator) const;
		void exportAllDataCSV() const { exportAllData(",", "\n"); }

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
		inline void saveVector3D(ofstream & outFile, const Vector3D & v, const string & horizontalSeparator, const string & verticalSeparator) const{
				outFile << 	v.x() << horizontalSeparator << 
							v.y() << horizontalSeparator << 
							v.z() << verticalSeparator;
		}

		inline void saveSphericalParticlePositionMatrix(ofstream & outFile, const SphericalParticlePtr & particle, const string & horizontalSeparator, const string & verticalSeparator) const{
			for(int i = 0 ; i <= particle->getTaylorOrder() ; ++i ){
				// Save each component of the i-th derivative of the positions
				outFile << horizontalSeparator;
				saveVector3D(outFile, particle->getPosition(i), horizontalSeparator, verticalSeparator);
			}
			outFile << verticalSeparator;
		}
		
		inline void saveSphericalParticleOrientationMatrix(ofstream & outFile, const SphericalParticlePtr & particle, const string & horizontalSeparator, const string & verticalSeparator) const{
			for(int i = 0 ; i <= particle->getTaylorOrder() ; ++i ){
				// Save each component of the i-th derivative of the orientations
				outFile << horizontalSeparator;
				saveVector3D(outFile, particle->getOrientation(i), horizontalSeparator, verticalSeparator);
			}
			outFile << verticalSeparator;
		}

}; // class SphericalParticlePtrArrayKit


#endif
