#define BOOST_TEST_MODULE IOLibTest

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
#include <readPhysicalEntity.h>

using namespace std;

TestCase( ReadEntityTest )
{
		string inputFile("../IOLibTest/inputEntity.txt");

		Entity entity1(5);

		Entity entity2 = readEntity(inputFile);

		checkEqual(entity1.getHandle(), entity2.getHandle());
}

TestCase( ReadPhysicalEntityTest )
{
		string inputFile("../IOLibTest/inputPhysicalEntity.txt");

		PhysicalEntity tester(4, 3, 3);
		PhysicalEntity tested = readPhysicalEntity(inputFile);

		//checkEqual(tester.getHandle(), tested.getHandle());
}