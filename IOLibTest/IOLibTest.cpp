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

// EntityLib
#include <Entity.h>
#include <PhysicalEntity.h>
#include <Particle.h>
#include <SphericalParticle.h>

// IOLib
#include <readEntity.h>
//#include <readPhysicalEntity.h>
//#include <readParticle.h>
//#include <readSphericalParticle.h>
#include <vectorIO.h>
#include <FileReader.h>

// PropertyLib
#include <PropertyContainer.h>

// boost
#include <boost/any.hpp>

using namespace std;

const string project_root_path = PROJECT_PATH;

TestCase( ReadEntityTest )
{
		string inputFile(project_root_path + "IOLibTest/inputEntity.txt");

		Entity entity1(5);

		EntityPtr entity2 = readEntity(inputFile);
		
		checkEqual(entity1.getHandle(), entity2->getHandle());
}

//
//TestCase( ReadPhysicalEntityTest )
//{
//		string inputFile(project_root_path + "IOLibTest/inputPhysicalEntity.txt");
//
//		PhysicalEntity tester(4, 3, 3);
//		PhysicalEntityPtr tested = readPhysicalEntity(inputFile);
//
//		checkEqual( tester.getHandle(), tested->getHandle() );
//		checkEqual( tester.getDimension(), tested->getDimension() );
//		checkEqual( tester.getTaylorOrder(), tested->getTaylorOrder() );
//}
//

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
		boost::any anyValue;

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
		checkEqual(boost::any_cast<int>(anyValue), intValue);
		fileReader.readAnyValue("<Double>", anyValue, defaultInputMethod<double>);
		checkEqual(boost::any_cast<double>(anyValue), doubleValue);
		fileReader.readAnyValue("<String>", anyValue, defaultInputMethod<string>);
		checkEqual(boost::any_cast<string>(anyValue), stringValue);
		fileReader.readAnyValue("<Vector3D>", anyValue, defaultInputMethod<Vector3D>);
		checkEqual(boost::any_cast<Vector3D>(anyValue), vector3DValue);
		
		checkEqual( readInteger, intValue );
		checkEqual( readDouble, doubleValue );
		checkEqual( readString, stringValue );
		checkEqual( readVector3d, vector3DValue );
		checkEqual( readVectorVector3D, vectorVector3DValue);
}