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

// UtilsLib
#include <Foreach.h>

// PropertyLib
#include <RawPropertyContainer.h>

// IOLib
#include <FileReader.h>

// boost
#include <boost/filesystem.hpp>

using namespace std;

class SphericalParticlePtrArrayKit : public SphericalParticlePtrArray
{
	public:
		SphericalParticlePtrArrayKit();
		virtual ~SphericalParticlePtrArrayKit();

		bool inputParticle(const string & inputPath);
		bool inputParticles(const int nParticles, const string & inputPath);
		bool inputParticles(const vector<string> & inputPath);

		void openFiles(const string & outputPath);

		void exportTemporalData(const string & horizontalSeparator, const string & verticalSeparator) const;
		void exportTemporalDataCSV() const { exportTemporalData(",", "\n"); }

		void exportAllData(const string & horizontalSeparator, const string & verticalSeparator) const;
		void exportAllDataCSV() const { exportAllData(",", "\n"); }

		void requireRawPropertyContainer( const RawPropertyContainer & required );

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

		RawPropertyContainer requiredProperties;

		bool readEntity( const string & fileName, EntityPtr & entity );
		bool readPhysicalEntity( const string & fileName, PhysicalEntityPtr & physicalEntity );
		bool readParticle( const string & fileName, ParticlePtr & particle );
		bool readSphericalParticle( const string & fileName, SphericalParticlePtr & sphericalParticle );

		/* These functions only make the program clearer */
		void saveVector3D(ofstream & outFile, const Vector3D & v, const string & horizontalSeparator, const string & verticalSeparator) const;
		void saveSphericalParticlePositionMatrix(ofstream & outFile, const SphericalParticlePtr & particle, const string & horizontalSeparator, const string & verticalSeparator) const;
		void saveSphericalParticleOrientationMatrix(ofstream & outFile, const SphericalParticlePtr & particle, const string & horizontalSeparator, const string & verticalSeparator) const;

}; // class SphericalParticlePtrArrayKit


#endif
