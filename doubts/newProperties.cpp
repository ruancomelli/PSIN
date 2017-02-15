// ==============================================================================================================================
// ==============================================================================================================================
// CollidingSpheres.cpp
// Include's, using's and global variables' definitions
// ==============================================================================================================================
// The following pseudo-code lines represent every include and using we want, inside every file
#include <everything>

using namespace all_of_them;

const string project_root_path = PROJECT_PATH;

// ==============================================================================================================================
// ==============================================================================================================================
// PropertyList.h
// Define properties and their relationship
// ==============================================================================================================================

// Assigns value to destination if value is positive
void setPositive( const double & value, double & destination);

double getVolumeFromRadius( const double & radius ){
	return 4/3 * pi * pow(radius, 3);
}

double getRadiusFromVolume(const double & volume){
	return pow( 3/(4*pi) * volume, 1/3 )
}

// Mass
RawProperty<double> mass("Mass", setPositive);

// Volume
RawProperty<double> volume("Volume", setPositive);

// Radius
RawProperty<double> radius("Radius", setPositive);

radius.deductibleFrom(volume, getRadiusFromVolume);
volume.deductibleFrom(radius, getVolumeFromRadius);


// ==============================================================================================================================
// ==============================================================================================================================
// RawPhysicalProperty
// ==============================================================================================================================

template<typename type>
void defaultSetter(const type & value, type & destination)
{
	destination = value;
}

template<typename type>
type defaultGetter(const type & value)
{
	return value;
}

template<typename interfaceType, typename storedType>
class RawPhysicalProperty
{
	public:
		// Constructors
		RawPhysicalProperty()
			: name("Nameless")
		{
			if( std::is_same<interfaceType, storedType>::value )	// If both classes are equal, we can use default setter and getter functions
			{
				setter = defaultSetter;
				getter = defaultGetter;
			}
		}

		explicit RawPhysicalProperty(const string & name)
		{
			if(!name.empty()) setName(name);
			else setName("Nameless");

			if( std::is_same<interfaceType, storedType>::value )	// If both classes are equal, we can use default setter and getter functions
			{
				setter = defaultSetter;
				getter = defaultGetter;
			}
		}

		RawPhysicalProperty(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &))
		{
			this->name = name;
			this->setter = setterFunction;
			this->getter = getterFunction;
		}

		// Set and get name
		void setName(const string & name)
		{
			if(!name.empty()) this->name = name;
		}

		string getName(void) const
		{
			return this->name;
		}

		// Set setter and getter
		void setSetterFunction( void (*setterFunction)(const interfaceType & value, storedType & destination) )
		{
			this->setter = setterFunction;
		}
		void setGetterFunction( interfaceType (*getterFunction)(const storedType & value) )
		{
			this->getter = getterFunction;
		}


	private:
		void (*setter)(const interfaceType & value, storedType & destination) = NULL;
		interfaceType (*getter)(const storedType &) = NULL;

		string name;

}; // class RawPhysicalProperty

template<typename...> class PhysicalProperty;	// Allows multiple template arguments

template<typename interfaceType, typename storedType>
class PhysicalProperty
{
	public:
		// Constructors
		PhysicalProperty()
		{}

		explicit PhysicalProperty(string name)
			: rawProperty(name)
		{}

		PhysicalProperty(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &))
			: rawProperty(name, setterFunction, getterFunction)
		{}

		// Setter and getter functions
		void set(const interfaceType & value)
		{
			rawProperty.setter(value, this->value);
		}

		interfaceType get(void)
		{
			return rawProperty.getter(this->value);
		}

	private:
		RawPhysicalProperty<interfaceType, storedType> rawProperty;
		storedType value;

}; // class PhysicalProperty


template<typename type>
class PhysicalProperty : public PhysicalProperty<type, type>
{};


// ==============================================================================================================================
// ==============================================================================================================================
// CollidingSpheres.cpp
// Main function
// ==============================================================================================================================
// Main function is the simulator. Obviously, this can be changed later, but this is not the target of this branch

int main(int argc, char **argv){
	// Simulation data
	string inputFolder(project_root_path + "_input/");
	FileReader simulationFileReader(inputFolder + "input.txt");
	string simulationName;
	simulationFileReader.readValue("<simulationName>", simulationName);

	FileReader inputData(inputFolder + simulationName + "/input.txt");
	double initialTime;
	double timeStep;
	double finalTime;
	int taylorOrder;
	int dimension;
	int numberOfParticles;
	int timeStepsForOutput;
	Vector3D gravity;

	inputData.readValue("<initialTime>", initialTime);
	inputData.readValue("<timeStep>", timeStep);
	inputData.readValue("<finalTime>", finalTime);
	inputData.readValue("<taylorOrder>", taylorOrder);
	inputData.readValue("<dimension>", dimension);
	inputData.readValue("<numberOfParticles>", numberOfParticles);
	inputData.readValue("<gravity>", gravity);
	inputData.readValue("<timeStepsForOutput>", timeStepsForOutput);

	string outputPath(project_root_path + "_output/" + simulationName + "/");

	boost::filesystem::path outputDir(outputPath);
	boost::filesystem::create_directory(outputDir);

	boost::filesystem::path MATLAB_outputDir(outputPath + "MATLAB_output/");
	boost::filesystem::create_directory(MATLAB_outputDir);

	// Input
	string particleInputFolder(inputFolder + simulationName + "/");

	SphericalParticlePtrArrayKit particleArray;


	// ----------------------------------------------------- begin NEW THINGS -----------------------------------------------------

	// Creating a new forceModel:
	ForceModel viscoSpheres;
	viscoSpheres.normalForceCalculationMethod( normalForceViscoelasticSpheres );
	viscoSpheres.tangentialForceCalculationMethod( tangentialForceHaffWerner );
	viscoSpheres.setName( "Viscoelastic Spheres" );
	viscoSpheres.requireProperty( "radius" );
	viscoSpheres.requireProperty( elasticModulus );
	viscoSpheres.requireProperty( dissipativeConstant );
	viscoSpheres.requireProperty( poissonRatio );
	viscoSpheres.requireProperty( mass );
	forceModelList.add(viscoSpheres);

	// ---

	ForceModel forceModel;	// This is the force model currently in use
	string forceModelName;

	inputData.readValue("<forceModel>", forceModelName);	// Read desired forceModel from input file

	extern vector<ForceModel> forceModelList;	// This is a list of ForceModel objects. Any new ForceModel instance can be added to the global forceModelList using forceModelList.append( newForceModel )
	foreach( ForceModel fm, forceModelList )	// This sets forceModel as required by the user
	{
		if( fm.getName() == forceModelName )
		{
			forceModel = fm;
			break;
		}
	}

	forceModel.requireProperties( particleArray ); // forceModel has a list of properties that particleArray must have in order to compute forces
	// OR
	particleArray.setRequiredProperties( forceModel.getRequiredProperties() );


	bool successfullInput = particleArray.inputParticles(numberOfParticles, particleInputFolder); // Inputs particles as required by the forceModel
	bool successfullPropertyDetermination = particleArray.checkPropertyRedundances();
	// Maybe in the input files there was not "Volume", but there was "Radius". We can easily deduce "Volume" through the expression Volume = 4/3 * pi * Radius
	// CAUTION: Actually, "Volume" is not always dependent on "Radius". This only happens to SphericalParticles

	if( !successfullInput ) // Checks whether all physical properties were successfully inputed
	{
		cerr 	<< "Error: The selected force model requires some properties that are not in input files" << endl
				<< "Required properties are:" << endl
				<< forceModel.requiredPropertiesNames() << endl;
	}

	// ----------------------------------------------------- end NEW THINGS -----------------------------------------------------


	foreach(SphericalParticlePtr particlePtr, particleArray){
		const double m = particlePtr->getScalarProperty( MASS );
		const double r = particlePtr->getScalarProperty( MASS );

		particlePtr->setScalarProperty( MOMENT_OF_INERTIA, 2 * m * r * r / 5 );
		particlePtr->setScalarProperty( VOLUME, 4 * boost::math::constants::pi<double>() * r * r * r / 3 );
	}

	particleArray[0]->setGravity(gravity);
	
	// Output
	particleArray.openFiles(outputPath);
	
	string verticalSeparator = "\n";
	string horizontalSeparator = ",";

	ofstream mainOutFile(outputPath + "output.txt");
	mainOutFile << "<nParticles> "		<< numberOfParticles	<< verticalSeparator;

	mainOutFile << "<initialTime> "		<< initialTime			<< verticalSeparator;
	mainOutFile << "<timeStep> "		<< timeStep				<< verticalSeparator;
	mainOutFile << "<finalTime> "		<< finalTime			<< verticalSeparator;

	mainOutFile << "<taylorOrder> "		<< taylorOrder			<< verticalSeparator;

	mainOutFile << "<timeStepsForOutput> "	<< timeStepsForOutput		<< verticalSeparator;

	ofstream timeVectorFile(outputPath + "timeVector.txt");
	ofstream timeVectorForPlotFile(outputPath + "timeVectorForPlot.txt");

	particleArray.exportAllDataCSV();
	timeVectorForPlotFile << 0 << verticalSeparator;

	// ===== Simulation =====
	ForceModel::setNumberOfParticles( numberOfParticles );

	foreach( SphericalParticlePtr particle, particleArray ){
		foreach( SphericalParticlePtr neighbor, particleArray ){
			if( neighbor->getHandle() > particle->getHandle() ){
				particle->addNeighbor( neighbor );
			}
		}
	}

	int timeStepsForOutputCounter = 0;

	for(double t = initialTime; t <= finalTime ; t += timeStep){

		timeVectorFile << t << verticalSeparator;

		// Set forces and torques to zero
		foreach( SphericalParticlePtr particle, particleArray ){
			particle->setContactForce( nullVector3D() );
			particle->setBodyForce( nullVector3D() );
			particle->setResultingTorque( nullVector3D() );
		}

		// Body forces
		foreach( SphericalParticlePtr particle, particleArray ){
			particle->addBodyForce(particle->getScalarProperty(MASS) * gravity);
		}

		// Predict position and orientation
		foreach( SphericalParticlePtr particle, particleArray ){
			particle->setPosition( ForceModel::taylorPredictor( particle->getPosition(), taylorOrder, timeStep ) );
			particle->setOrientation( ForceModel::taylorPredictor( particle->getOrientation(), taylorOrder, timeStep ) );
		}

		// Contact forces
		
		foreach( SphericalParticlePtr particle, particleArray ){
			foreach( int handle, particle->getNeighborhood() ){
				SphericalParticlePtr neighbor = particleArray[handle];

				if(particle->touches(neighbor))	// If particles are in touch
				{

	// ----------------------------------------------------- begin NEW THINGS -----------------------------------------------------

					forceModel.calculate(particle, neighbor)

	// ----------------------------------------------------- end NEW THINGS -----------------------------------------------------
				}
			}
		}

		// Correct position and orientation
		foreach( SphericalParticlePtr particle, particleArray ){
			ForceModel::correctPosition( particle , taylorOrder, timeStep );
			ForceModel::correctOrientation( particle , taylorOrder, timeStep );
		}


		// ----- Saving to file -----

		// Prints every derivative of particles' position
		if( (++timeStepsForOutputCounter) == timeStepsForOutput){
			timeStepsForOutputCounter = 0;

			particleArray.exportTemporalDataCSV();

			timeVectorForPlotFile << t << verticalSeparator;
		}
	}

	mainOutFile.close();
	timeVectorFile.close();
	timeVectorForPlotFile.close();
	
	cout << endl << "Success" << endl << endl;
}
// ==============================================================================================================================
// ==============================================================================================================================
