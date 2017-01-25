#include <SphericalParticlePtrArrayKit.h>

// ------------------------------- Constructor -------------------------------

SphericalParticlePtrArrayKit::SphericalParticlePtrArrayKit() : isReady(false)
{

}

SphericalParticlePtrArrayKit::~SphericalParticlePtrArrayKit()
{
	for( unsigned i=0 ; i<this->outFile.size() ; ++i ){
		for( unsigned j=0 ; j<this->outFile[i].size() ; ++j ){
			outFile[i][j]->close();
		}
	}
}

void SphericalParticlePtrArrayKit::inputParticle(string & inputPath)
{
	SphericalParticlePtr sphericalParticlePtr = readSphericalParticle(inputPath);

	if(sphericalParticlePtr->getHandle() < 0)
		sphericalParticlePtr->setHandle( this->size() + 1 );

	this->push_back( sphericalParticlePtr );
}

void SphericalParticlePtrArrayKit::inputParticles(int nParticles, string & inputPath)
{
	for(int i=0 ; i<nParticles ; ++i)
	{
		string particleInputPath = inputPath + "particle" + _itoa(i, new char[100], 10) + ".txt";
		this->inputParticle(particleInputPath);
	}
}

void SphericalParticlePtrArrayKit::inputParticles(vector<string> & inputPath)
{
	for( unsigned i=0; i<inputPath.size(); ++i)
	{
		this->inputParticle(inputPath[i]);
	}
}

void SphericalParticlePtrArrayKit::openFiles(string outputPath)
{
	this->outFile.resize( this->size() );

	foreach(SphericalParticlePtr particlePtr, *this)
	{

		string particleOutputPath = outputPath + "Particle" + _itoa(particlePtr->getHandle(), new char[100], 10) + "/";
		_mkdir(particleOutputPath.c_str());

		outFile[particlePtr->getHandle()].resize( N_FILES_PER_PARTICLE );

		this->outFile[particlePtr->getHandle()][DATA_IDX					] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "data.txt")); 
		this->outFile[particlePtr->getHandle()][FORCE_IDX					] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "force.txt")); 
		this->outFile[particlePtr->getHandle()][TORQUE_IDX					] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "torque.txt")); 
		this->outFile[particlePtr->getHandle()][POSITION_MATRIX_IDX			] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "position_matrix.txt")); 
		this->outFile[particlePtr->getHandle()][ORIENTATION_MATRIX_IDX		] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "orientation_matrix.txt")); 
		this->outFile[particlePtr->getHandle()][POSITION_IDX				] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "position.txt")); 
		this->outFile[particlePtr->getHandle()][ORIENTATION_IDX				] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "orientation.txt")); 
		this->outFile[particlePtr->getHandle()][VELOCITY_IDX				] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "velocity.txt")); 
		this->outFile[particlePtr->getHandle()][ROTATIONAL_VELOCITY_IDX		] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "rotational_velocity.txt")); 
		this->outFile[particlePtr->getHandle()][LINEAR_MOMENTUM_IDX			] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "linear_momentum.txt")); 
		this->outFile[particlePtr->getHandle()][ANGULAR_MOMENTUM_IDX		] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "angular_momentum.txt")); 
		this->outFile[particlePtr->getHandle()][MECHANICAL_ENERGY_IDX		] = SharedPointer<ofstream>( new ofstream(particleOutputPath + "energy.txt")); 

	}

	this->isReady = true;
}


void SphericalParticlePtrArrayKit::exportTemporalData(string horizontalSeparator, string verticalSeparator)
{
	if(this->isReady){
		foreach(SphericalParticlePtr particlePtr, *this){
			saveSphericalParticlePositionMatrix(*outFile[particlePtr->getHandle()][POSITION_MATRIX_IDX],
				*particlePtr, horizontalSeparator, verticalSeparator);

			saveSphericalParticleOrientationMatrix(*outFile[particlePtr->getHandle()][ORIENTATION_MATRIX_IDX],
				*particlePtr, horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][FORCE_IDX],
				particlePtr->getResultingForce(), horizontalSeparator, verticalSeparator);

			saveVector3D(*outFile[particlePtr->getHandle()][TORQUE_IDX],
				particlePtr->getResultingTorque(), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][POSITION_IDX],
				particlePtr->getPosition(0), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][ORIENTATION_IDX],
				particlePtr->getOrientation(0), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][VELOCITY_IDX],
				particlePtr->getPosition(1), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][ROTATIONAL_VELOCITY_IDX],
				particlePtr->getOrientation(1), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][LINEAR_MOMENTUM_IDX],
				particlePtr->getLinearMomentum(), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][ANGULAR_MOMENTUM_IDX],
				particlePtr->getAngularMomentum(), horizontalSeparator, verticalSeparator);
			
			*outFile[particlePtr->getHandle()][MECHANICAL_ENERGY_IDX] << particlePtr->getMechanicalEnergy() << verticalSeparator;
		}
	}
	else
	{
		cerr << "Particle array is not ready to export data." << endl;
	}
}

void SphericalParticlePtrArrayKit::exportAllData(string horizontalSeparator, string verticalSeparator)
{
	if(this->isReady)
	{
		foreach(SphericalParticlePtr particlePtr, *this){
			*outFile[particlePtr->getHandle()][DATA_IDX] << "<Radius> " << particlePtr->getGeometricParameter(RADIUS) << verticalSeparator;

			saveSphericalParticlePositionMatrix(*outFile[particlePtr->getHandle()][POSITION_MATRIX_IDX],
				*particlePtr, horizontalSeparator, verticalSeparator);

			saveSphericalParticleOrientationMatrix(*outFile[particlePtr->getHandle()][ORIENTATION_MATRIX_IDX],
				*particlePtr, horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][FORCE_IDX],
				particlePtr->getResultingForce(), horizontalSeparator, verticalSeparator);

			saveVector3D(*outFile[particlePtr->getHandle()][TORQUE_IDX],
				particlePtr->getResultingTorque(), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][POSITION_IDX],
				particlePtr->getPosition(0), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][ORIENTATION_IDX],
				particlePtr->getOrientation(0), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][VELOCITY_IDX],
				particlePtr->getPosition(1), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][ROTATIONAL_VELOCITY_IDX],
				particlePtr->getOrientation(1), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][LINEAR_MOMENTUM_IDX],
				particlePtr->getLinearMomentum(), horizontalSeparator, verticalSeparator);
			
			saveVector3D(*outFile[particlePtr->getHandle()][ANGULAR_MOMENTUM_IDX],
				particlePtr->getAngularMomentum(), horizontalSeparator, verticalSeparator);
			
			*outFile[particlePtr->getHandle()][MECHANICAL_ENERGY_IDX] << particlePtr->getMechanicalEnergy() << verticalSeparator;
		}
	}
	else
	{
		cerr << "Particle array is not ready to export data." << endl;
	}
}