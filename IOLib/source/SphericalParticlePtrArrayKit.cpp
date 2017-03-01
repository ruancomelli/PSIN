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

bool SphericalParticlePtrArrayKit::inputParticle(const string & inputPath)
{
	bool boolFlag;

	SphericalParticlePtr sphericalParticlePtr( new SphericalParticle() );
	boolFlag = readSphericalParticle(inputPath, sphericalParticlePtr);

	if(sphericalParticlePtr->getHandle() < 0)
		sphericalParticlePtr->setHandle( this->size() + 1 );

	this->push_back( sphericalParticlePtr );

	return boolFlag;
}

bool SphericalParticlePtrArrayKit::inputParticles(const int nParticles, const string & inputPath)
{
	bool boolFlag = true;

	for(int i=0 ; i<nParticles ; ++i)
	{
		string particleInputPath = inputPath + "particle" + to_string(i) + ".txt";
		boolFlag = boolFlag && this->inputParticle(particleInputPath);
	}

	return boolFlag;
}

bool SphericalParticlePtrArrayKit::inputParticles(const vector<string> & inputPath)
{
	bool boolFlag = true;

	for( unsigned i=0; i<inputPath.size(); ++i)
	{
		boolFlag = boolFlag && this->inputParticle(inputPath[i]);
	}

	return boolFlag;
}

void SphericalParticlePtrArrayKit::openFiles(const string & outputPath)
{
	this->outFile.resize( this->size() );

	foreach(SphericalParticlePtr particlePtr, *this)
	{

		string particleOutputPath = outputPath + "Particle" + to_string(particlePtr->getHandle()) + "/";
		boost::filesystem::path particleOutputDir(particleOutputPath);
		boost::filesystem::create_directory(particleOutputDir);

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

		// We must check if all files were successfully opened

	}

	this->isReady = true;
}


void SphericalParticlePtrArrayKit::exportTemporalData(const string & horizontalSeparator, const string & verticalSeparator) const
{
	if(this->isReady){
		foreach(SphericalParticlePtr particlePtr, *this){
			saveSphericalParticlePositionMatrix(*outFile[particlePtr->getHandle()][POSITION_MATRIX_IDX],
				particlePtr, horizontalSeparator, verticalSeparator);

			saveSphericalParticleOrientationMatrix(*outFile[particlePtr->getHandle()][ORIENTATION_MATRIX_IDX],
				particlePtr, horizontalSeparator, verticalSeparator);
			
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

void SphericalParticlePtrArrayKit::exportAllData(const string & horizontalSeparator, const string & verticalSeparator) const
{
	if(this->isReady)
	{
		foreach(SphericalParticlePtr particlePtr, *this){
			*outFile[particlePtr->getHandle()][DATA_IDX] << "<Radius> " << particlePtr->getGeometricParameter(RADIUS) << verticalSeparator;


			for( auto& name : *(requiredProperties.getPropertyNames()) )
			{
				auto outputMethod = this->requiredProperties.getOutputMethod(name);
				*outFile[particlePtr->getHandle()][DATA_IDX] << "<" + name + "> ";
				outputMethod(*outFile[particlePtr->getHandle()][DATA_IDX], particlePtr->getAsAnyValue(name));
				*outFile[particlePtr->getHandle()][DATA_IDX] << endl;
			}

			saveSphericalParticlePositionMatrix(*outFile[particlePtr->getHandle()][POSITION_MATRIX_IDX],
				particlePtr, horizontalSeparator, verticalSeparator);

			saveSphericalParticleOrientationMatrix(*outFile[particlePtr->getHandle()][ORIENTATION_MATRIX_IDX],
				particlePtr, horizontalSeparator, verticalSeparator);
			
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

void SphericalParticlePtrArrayKit::requireRawPropertyContainer( const RawPropertyContainer & required )
{
	this->requiredProperties = required;
}

bool SphericalParticlePtrArrayKit::readEntity( const string & fileName, EntityPtr & newEntity ){
	FileReader fileReader(fileName);

	bool boolFlag = true;

	// ----- Read Handle -----
	int handle;
	boolFlag = boolFlag && fileReader.readValue("<Handle>", handle);

	newEntity = EntityPtr( new Entity(handle) );

	return boolFlag;
}

bool SphericalParticlePtrArrayKit::readPhysicalEntity( const string & fileName, PhysicalEntityPtr & newPhysicalEntity )
{
	FileReader fileReader(fileName);
	bool boolFlag = true;

	// ----- Read Entity -----
	EntityPtr entity( new Entity() );
	boolFlag = boolFlag && readEntity(fileName, entity);
	

	// ----- Read taylorOrder -----
	int taylorOrder;
	boolFlag = boolFlag && fileReader.readValue("<TaylorOrder>", taylorOrder);

	// ----- Read dimension -----
	int dimension;
	boolFlag = boolFlag && fileReader.readValue("<Dimension>", dimension);

	// ----- Create object -----
	PhysicalEntity physicalEntity( taylorOrder, dimension, *entity );


	// ----- Read initial position -----
	int size = taylorOrder + 1;

	vector<Vector3D> position;
	position.resize(size);
	fileReader.readValue("<Position>", position);
	physicalEntity.setPosition(position);

	// ----- Read initial orientation -----
	vector<Vector3D> orientation;
	orientation.resize(size);
	fileReader.readValue("<Orientation>", orientation);
	physicalEntity.setOrientation(orientation);

	// ----- Read physical properties -----
	// Set propertyContainer
	physicalEntity.requireProperties( this->requiredProperties );

	// Scalar Properties
	for( auto& name : *(requiredProperties.getPropertyNames()) )
	{
		Any value;
		fileReader.readAnyValue("<" + name + ">", 
			value, 
			this->requiredProperties.getInputMethod(name) );

		physicalEntity.set( name, value );
	}

	newPhysicalEntity = PhysicalEntityPtr( new PhysicalEntity(physicalEntity) );

	return boolFlag;
}

bool SphericalParticlePtrArrayKit::readParticle( const string & fileName, ParticlePtr & particle )
{
	bool boolFlag = true;

	PhysicalEntityPtr physicalEntity( new PhysicalEntity() );
	boolFlag = boolFlag && readPhysicalEntity(fileName, physicalEntity);

	particle = ParticlePtr( new Particle(*physicalEntity) );

	return boolFlag;
}

bool SphericalParticlePtrArrayKit::readSphericalParticle( const string & fileName, SphericalParticlePtr & sphericalParticle )
{
	bool boolFlag = true;

	FileReader fileReader(fileName);

	// ----- Read Particle -----
	ParticlePtr particle( new Particle() );
	boolFlag = boolFlag && readParticle(fileName, particle);
	
	// ----- Read SphericalParticle -----
	sphericalParticle = SphericalParticlePtr( new SphericalParticle(*particle) );

	DoubleVector geometricParameter(N_GEOMETRIC_PARAMETER);
	boolFlag = boolFlag && fileReader.readValue("<Radius>", geometricParameter[RADIUS]);

	sphericalParticle->setGeometricParameter(geometricParameter);

	return boolFlag;
}



void SphericalParticlePtrArrayKit::saveVector3D(ofstream & outFile, const Vector3D & v, const string & horizontalSeparator, const string & verticalSeparator) const{
		outFile << 	v.x() << horizontalSeparator << 
					v.y() << horizontalSeparator << 
					v.z() << verticalSeparator;
}

void SphericalParticlePtrArrayKit::saveSphericalParticlePositionMatrix(ofstream & outFile, const SphericalParticlePtr & particle, const string & horizontalSeparator, const string & verticalSeparator) const{
	for(int i = 0 ; i <= particle->getTaylorOrder() ; ++i ){
		// Save each component of the i-th derivative of the positions
		outFile << horizontalSeparator;
		saveVector3D(outFile, particle->getPosition(i), horizontalSeparator, verticalSeparator);
	}
	outFile << verticalSeparator;
}

void SphericalParticlePtrArrayKit::saveSphericalParticleOrientationMatrix(ofstream & outFile, const SphericalParticlePtr & particle, const string & horizontalSeparator, const string & verticalSeparator) const{
	for(int i = 0 ; i <= particle->getTaylorOrder() ; ++i ){
		// Save each component of the i-th derivative of the orientations
		outFile << horizontalSeparator;
		saveVector3D(outFile, particle->getOrientation(i), horizontalSeparator, verticalSeparator);
	}
	outFile << verticalSeparator;
}