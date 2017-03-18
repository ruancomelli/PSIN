#define BOOST_TEST_MODULE IOLibTest
//#define PROJECT_PATH "D:\\Git-Projects\\ParticleSimulator\\"
//#define PROJECT_PATH "D:/Git-Projects/ParticleSimulator/"

// Standard
#include <string>

// UtilsLib
#include <Mathematics.h>
#include <Vector3D.h>
#include <Vector.h>
#include <Test.h>
#include <Foreach.h>
#include <Any.h>

// EntityLib
#include <Entity.h>
#include <PhysicalEntity.h>
#include <Particle.h>
#include <SphericalParticle.h>

// IOLib
#include <vectorIO.h>
#include <FileReader.h>
#include <SphericalParticlePtrArrayKit.h>

// PropertyLib
#include <PropertyContainer.h>
#include <PropertyDefinitions.h>

using namespace std;
using namespace PropertyDefinitions;

const string project_root_path = PROJECT_PATH;

TestCase( VectorVector3DTest )
{
		vector<Vector3D> tester(4);
		tester[0] = Vector3D(1.0, 1.0, 1.0);
		tester[1] = Vector3D(2.0, 4.0, 8.0);
		tester[2] = Vector3D(3.0, 9.0, 27.0);
		tester[3] = Vector3D(4.0, 16.0, 64.0);

		string fileName(project_root_path + "IOLibTest/VectorVector3DTestInput.txt");

		ifstream file(fileName);

		if(!file){
			cerr << "Error opening file " << fileName << endl << endl;
			system("pause");
			exit(EXIT_FAILURE);
		}

		file.clear(); // THIS IS ABSOLUTELY NECESSARY!!!
		file.seekg(ios_base::beg);

		Vector3D line1;
		Vector3D line2;
		Vector3D line3;
		Vector3D line4;

		file >> line1;
		file >> line2;
		file >> line3;
		file >> line4;

		checkClose(tester[0].x(), line1.x(), 1e-2);
		checkClose(tester[0].y(), line1.y(), 1e-2);
		checkClose(tester[0].z(), line1.z(), 1e-2);
		
		checkClose(tester[1].x(), line2.x(), 1e-2);
		checkClose(tester[1].y(), line2.y(), 1e-2);
		checkClose(tester[1].z(), line2.z(), 1e-2);
		
		checkClose(tester[2].x(), line3.x(), 1e-2);
		checkClose(tester[2].y(), line3.y(), 1e-2);
		checkClose(tester[2].z(), line3.z(), 1e-2);
		
		checkClose(tester[3].x(), line4.x(), 1e-2);
		checkClose(tester[3].y(), line4.y(), 1e-2);
		checkClose(tester[3].z(), line4.z(), 1e-2);

		// First method
		file.clear(); // THIS IS ABSOLUTELY NECESSARY!!!
		file.seekg(ios_base::beg);

		vector<Vector3D> tested(4);
		file >> tested;

		checkClose(tester[0].x(), tested[0].x(), 1e-2);
		checkClose(tester[0].y(), tested[0].y(), 1e-2);
		checkClose(tester[0].z(), tested[0].z(), 1e-2);
									   
		checkClose(tester[1].x(), tested[1].x(), 1e-2);
		checkClose(tester[1].y(), tested[1].y(), 1e-2);
		checkClose(tester[1].z(), tested[1].z(), 1e-2);
									   
		checkClose(tester[2].x(), tested[2].x(), 1e-2);
		checkClose(tester[2].y(), tested[2].y(), 1e-2);
		checkClose(tester[2].z(), tested[2].z(), 1e-2);
									   
		checkClose(tester[3].x(), tested[3].x(), 1e-2);
		checkClose(tester[3].y(), tested[3].y(), 1e-2);
		checkClose(tester[3].z(), tested[3].z(), 1e-2);
		
		// Second method
		file.clear(); // THIS IS ABSOLUTELY NECESSARY!!!
		file.seekg(ios_base::beg);

		for(unsigned i = 0; i < tested.size(); ++i){
			file >> tested[i];
		}

		checkClose(tester[0].x(), tested[0].x(), 1e-2);
		checkClose(tester[0].y(), tested[0].y(), 1e-2);
		checkClose(tester[0].z(), tested[0].z(), 1e-2);
									   
		checkClose(tester[1].x(), tested[1].x(), 1e-2);
		checkClose(tester[1].y(), tested[1].y(), 1e-2);
		checkClose(tester[1].z(), tested[1].z(), 1e-2);
									   
		checkClose(tester[2].x(), tested[2].x(), 1e-2);
		checkClose(tester[2].y(), tested[2].y(), 1e-2);
		checkClose(tester[2].z(), tested[2].z(), 1e-2);
									   
		checkClose(tester[3].x(), tested[3].x(), 1e-2);
		checkClose(tester[3].y(), tested[3].y(), 1e-2);
		checkClose(tester[3].z(), tested[3].z(), 1e-2);

		
		// Third method
		file.clear(); // THIS IS ABSOLUTELY NECESSARY!!!
		file.seekg(ios_base::beg);

		file >> tested[0];
		file >> tested[1];
		file >> tested[2];
		file >> tested[3];

		checkClose(tester[0].x(), tested[0].x(), 1e-2);
		checkClose(tester[0].y(), tested[0].y(), 1e-2);
		checkClose(tester[0].z(), tested[0].z(), 1e-2);
									   
		checkClose(tester[1].x(), tested[1].x(), 1e-2);
		checkClose(tester[1].y(), tested[1].y(), 1e-2);
		checkClose(tester[1].z(), tested[1].z(), 1e-2);
									   
		checkClose(tester[2].x(), tested[2].x(), 1e-2);
		checkClose(tester[2].y(), tested[2].y(), 1e-2);
		checkClose(tester[2].z(), tested[2].z(), 1e-2);
									   
		checkClose(tester[3].x(), tested[3].x(), 1e-2);
		checkClose(tester[3].y(), tested[3].y(), 1e-2);
		checkClose(tester[3].z(), tested[3].z(), 1e-2);
		
		// Fourth method
		file.clear(); // THIS IS ABSOLUTELY NECESSARY!!!
		file.seekg(ios_base::beg);

		file >> line1;
		tested[0] = line1;
		
		file >> line2;
		tested[1] = line2;

		file >> line3;
		tested[2] = line3;
		
		file >> line4;
		tested[3] = line4;

		checkClose(tester[0].x(), tested[0].x(), 1e-2);
		checkClose(tester[0].y(), tested[0].y(), 1e-2);
		checkClose(tester[0].z(), tested[0].z(), 1e-2);
									   
		checkClose(tester[1].x(), tested[1].x(), 1e-2);
		checkClose(tester[1].y(), tested[1].y(), 1e-2);
		checkClose(tester[1].z(), tested[1].z(), 1e-2);
									   
		checkClose(tester[2].x(), tested[2].x(), 1e-2);
		checkClose(tester[2].y(), tested[2].y(), 1e-2);
		checkClose(tester[2].z(), tested[2].z(), 1e-2);
									   
		checkClose(tester[3].x(), tested[3].x(), 1e-2);
		checkClose(tester[3].y(), tested[3].y(), 1e-2);
		checkClose(tester[3].z(), tested[3].z(), 1e-2);

		file.close();
}


TestCase( FileReaderTest )
{
		string fileName(project_root_path + "IOLibTest/input.txt");
		int intValue = 5;
		double doubleValue = 3.1415;
		string stringValue = "Rohan";
		Vector3D vector3DValue(5.0, 1.0, 15.0);
		vector<Vector3D> vectorVector3DValue(4);
		Any anyValue;

		vectorVector3DValue[0] = Vector3D(1, 1, 1);
		vectorVector3DValue[1] = Vector3D(2, 4, 8);
		vectorVector3DValue[2] = Vector3D(3, 9, 27);
		vectorVector3DValue[3] = Vector3D(4, 16, 64);

		FileReader fileReader(fileName);

		int readInteger;
		double readDouble;
		string readString;
		Vector3D readVector3d;
		vector<Vector3D> readVectorVector3D(4);
		
		fileReader.readValue("<Integer>", readInteger);
		fileReader.readValue("<Double>", readDouble);
		fileReader.readValue("<String>", readString);
		fileReader.readValue("<Vector3D>", readVector3d);
		fileReader.readValue("<VectorVector3D>", readVectorVector3D);

		fileReader.readAnyValue("<Integer>", anyValue, defaultInputMethod<int>);
		checkEqual(anyCast<int>(anyValue), intValue);
		fileReader.readAnyValue("<Double>", anyValue, defaultInputMethod<double>);
		checkEqual(anyCast<double>(anyValue), doubleValue);
		fileReader.readAnyValue("<String>", anyValue, defaultInputMethod<string>);
		checkEqual(anyCast<string>(anyValue), stringValue);
		fileReader.readAnyValue("<Vector3D>", anyValue, defaultInputMethod<Vector3D>);
		checkEqual(anyCast<Vector3D>(anyValue), vector3DValue);
		
		checkEqual( readInteger, intValue );
		checkEqual( readDouble, doubleValue );
		checkEqual( readString, stringValue );
		checkEqual( readVector3d, vector3DValue );
		checkEqual( readVectorVector3D, vectorVector3DValue);
}

#include <RawPropertyContainer.h>
#include <PropertyDefinitions.h>

// For the next tests to work (ReadEntity, ReadPhysicalEntity, ReadParticle, ReadSphericalParticle),
// it is needed to move readEntity, readPhysicalEntity, readParticle and readSphericalParticle
// from private to public in class SphericalParticlePtrArrayKit

//TestCase(ReadEntity)
//{
//	string fileName = "readEntity.txt";
//
//	int handle = 3;
//
//	ofstream file(fileName);
//	file << "<Handle> " << handle << endl;
//	file.close();
//
//	SphericalParticlePtrArrayKit particleArray;
//	EntityPtr entity( new Entity() );
//	particleArray.readEntity(fileName, entity);
//
//	checkEqual(entity->getHandle(), handle );
//}

//TestCase(ReadPhysicalEntity)
//{
//	RawPropertyContainer raw;
//	raw.addProperty(PropertyDefinitions::mass);
//
//	int dimension = 3;
//	int taylorOrder = 4;
//	int handle = 10;
//	double massValue = 5.6;
//
//	vector<Vector3D> position = {
//		Vector3D(0.0, 0.1, 0.2),
//		Vector3D(0.3, 0.4, 0.5),
//		Vector3D(0.6, 0.7, 0.8),
//		Vector3D(0.9, 1.0, 1.2),
//		Vector3D(-0.1, -0.2, -0.3)
//	};
//	vector<Vector3D> orientation = {
//		Vector3D(1.3, 1.4, 1.5),
//		Vector3D(1.6, 1.7, 1.8),
//		Vector3D(1.9, 2.0, 2.1),
//		Vector3D(2.2, 2.3, 2.4),
//		Vector3D(2.5, 2.6, 2.7)
//	};
//
//	string fileName = "readPhysicalEntity.txt";
//
//	ofstream file(fileName);
//	file << "<Dimension> " << dimension << endl
//		<< "<TaylorOrder> " << taylorOrder << endl
//		<< "<Handle> " << handle << endl
//		<< "<Position> " << endl << position << endl
//		<< "<Orientation> " << endl << orientation << endl
//		<< "<Mass> " << massValue << endl;
//	file.close();
//
//	SphericalParticlePtrArrayKit particleArray;
//
//	particleArray.requireRawPropertyContainer(raw);
//
//	PhysicalEntityPtr physicalEntity( new PhysicalEntity() );
//	check( particleArray.readPhysicalEntity(fileName, physicalEntity) );
//
//	checkEqual(physicalEntity->getDimension(), dimension );
//	checkEqual(physicalEntity->getTaylorOrder(), taylorOrder);
//	checkEqual(physicalEntity->getHandle(), handle);
//	checkEqual(physicalEntity->getPosition(), position);
//	checkEqual(physicalEntity->getOrientation(), orientation);
//	checkEqual(physicalEntity->get( mass ), massValue);
//}
//
//TestCase(ReadParticle)
//{
//	RawPropertyContainer raw;
//	raw.addProperty(PropertyDefinitions::mass);
//
//	int dimension = 3;
//	int taylorOrder = 4;
//	int handle = 10;
//	double massValue = 5.6;
//
//	vector<Vector3D> position = {
//		Vector3D(0.0, 0.1, 0.2),
//		Vector3D(0.3, 0.4, 0.5),
//		Vector3D(0.6, 0.7, 0.8),
//		Vector3D(0.9, 1.0, 1.2),
//		Vector3D(-0.1, -0.2, -0.3)
//	};
//	vector<Vector3D> orientation = {
//		Vector3D(1.3, 1.4, 1.5),
//		Vector3D(1.6, 1.7, 1.8),
//		Vector3D(1.9, 2.0, 2.1),
//		Vector3D(2.2, 2.3, 2.4),
//		Vector3D(2.5, 2.6, 2.7)
//	};
//
//	string fileName = "readParticle.txt";
//
//	ofstream file(fileName);
//	file << "<Dimension> " << dimension << endl
//		<< "<TaylorOrder> " << taylorOrder << endl
//		<< "<Handle> " << handle << endl
//		<< "<Position> " << endl << position << endl
//		<< "<Orientation> " << endl << orientation << endl
//		<< "<Mass> " << massValue << endl;
//	file.close();
//
//	SphericalParticlePtrArrayKit particleArray;
//
//	particleArray.requireRawPropertyContainer(raw);
//
//	ParticlePtr particle(new Particle());
//	check(particleArray.readParticle(fileName, particle));
//
//	checkEqual(particle->getDimension(), dimension);
//	checkEqual(particle->getTaylorOrder(), taylorOrder);
//	checkEqual(particle->getHandle(), handle);
//	checkEqual(particle->getPosition(), position);
//	checkEqual(particle->getOrientation(), orientation);
//	checkEqual(particle->get(mass), massValue);
//}
//
//TestCase(ReadSphericalParticle)
//{
//	RawPropertyContainer raw;
//	raw.addProperty(PropertyDefinitions::mass);
//
//	int dimension = 3;
//	int taylorOrder = 4;
//	int handle = 10;
//	double massValue = 5.6;
//	double radius = 9.7;
//
//	vector<Vector3D> position = {
//		Vector3D(0.0, 0.1, 0.2),
//		Vector3D(0.3, 0.4, 0.5),
//		Vector3D(0.6, 0.7, 0.8),
//		Vector3D(0.9, 1.0, 1.2),
//		Vector3D(-0.1, -0.2, -0.3)
//	};
//	vector<Vector3D> orientation = {
//		Vector3D(1.3, 1.4, 1.5),
//		Vector3D(1.6, 1.7, 1.8),
//		Vector3D(1.9, 2.0, 2.1),
//		Vector3D(2.2, 2.3, 2.4),
//		Vector3D(2.5, 2.6, 2.7)
//	};
//
//	string fileName = "readSphericalParticle.txt";
//
//	ofstream file(fileName);
//	file << "<Dimension> " << dimension << endl
//		<< "<TaylorOrder> " << taylorOrder << endl
//		<< "<Handle> " << handle << endl
//		<< "<Position> " << endl << position << endl
//		<< "<Orientation> " << endl << orientation << endl
//		<< "<Mass> " << massValue << endl
//		<< "<Radius> " << radius << endl;
//	file.close();
//
//	SphericalParticlePtrArrayKit particleArray;
//
//	particleArray.requireRawPropertyContainer(raw);
//
//	SphericalParticlePtr sphericalParticle(new SphericalParticle());
//	check(particleArray.readSphericalParticle(fileName, sphericalParticle));
//
//	checkEqual(sphericalParticle->getDimension(), dimension);
//	checkEqual(sphericalParticle->getTaylorOrder(), taylorOrder);
//	checkEqual(sphericalParticle->getHandle(), handle);
//	checkEqual(sphericalParticle->getPosition(), position);
//	checkEqual(sphericalParticle->getOrientation(), orientation);
//	checkEqual(sphericalParticle->get(mass), massValue);
//	checkEqual(sphericalParticle->getGeometricParameter( RADIUS ), radius);
//}

// vector 3D IO

TestCase( IntVectorInput ){
	string fileName = "../UtilsLibTest/fileVector.txt";

	// Output
	std::ofstream outFile(fileName);

	vector<int> tester(5);
		tester[0] = 3;
		tester[1] = 1;
		tester[2] = 4;
		tester[3] = 1;
		tester[4] = 5;

	outFile << tester;
	outFile.close();

	// Input
	std::ifstream inFile(fileName);

	vector<int> tested(5);

	inFile >> tested;

	check( tester == tested );

	inFile.close();
}

TestCase( Vector3DIO ){
	string fileName("../UtilsLibTest/fileVector3D.txt");

	// Output
	Vector3D outVector(3.14159, 2.718281, 1.6180339);
	std::ofstream outFile(fileName);
	outFile << outVector;
	outFile.close();

	// Input
	Vector3D inVector;
	std::ifstream inFile(fileName);
	inFile >> inVector;
	inFile.close();

	checkClose(inVector.x(), outVector.x(), 1e-2);
	checkClose(inVector.y(), outVector.y(), 1e-2);
	checkClose(inVector.z(), outVector.z(), 1e-2);
}


#include <RawPropertyContainer.h>
#include <PropertyDefinitions.h>

TestCase(InputParticle)
{
		Property<string> color("Color");

		RawPropertyContainer raw;
		raw.addProperty(PropertyDefinitions::mass);
		raw.addProperty(color);
	
		int dimension = 3;
		int taylorOrder = 4;
		int handle = 10;

		double massValue = 5.6;
		string colorValue = "Blue";

		double radius = 9.7;
	
		vector<Vector3D> position = {
			Vector3D(0.0, 0.1, 0.2),
			Vector3D(0.3, 0.4, 0.5),
			Vector3D(0.6, 0.7, 0.8),
			Vector3D(0.9, 1.0, 1.2),
			Vector3D(-0.1, -0.2, -0.3)
		};
		vector<Vector3D> orientation = {
			Vector3D(1.3, 1.4, 1.5),
			Vector3D(1.6, 1.7, 1.8),
			Vector3D(1.9, 2.0, 2.1),
			Vector3D(2.2, 2.3, 2.4),
			Vector3D(2.5, 2.6, 2.7)
		};
	
		string fileName = "inputParticle.txt";
	
		ofstream file(fileName);
		file << "<Dimension> " << dimension << endl
			<< "<TaylorOrder> " << taylorOrder << endl
			<< "<Handle> " << handle << endl
			<< "<Position> " << endl << position << endl
			<< "<Orientation> " << endl << orientation << endl
			<< "<Mass> " << massValue << endl
			<< "<Color> " << colorValue << endl
			<< "<Radius> " << radius << endl;
		file.close();
	
		SphericalParticlePtrArrayKit particleArray;
	
		particleArray.requireRawPropertyContainer(raw);
	
		check(particleArray.inputParticle(fileName));

		SphericalParticlePtr sph = particleArray[0];
	
		checkEqual(sph->getDimension(), dimension);
		checkEqual(sph->getTaylorOrder(), taylorOrder);
		checkEqual(sph->getHandle(), handle);
		checkEqual(sph->getPosition(), position);
		checkEqual(sph->getOrientation(), orientation);
		checkEqual(sph->get(mass), massValue);
		checkEqual(sph->get(color), colorValue);
		checkEqual(sph->getGeometricParameter( RADIUS ), radius);
}