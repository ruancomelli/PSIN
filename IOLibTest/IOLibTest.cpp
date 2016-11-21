#define BOOST_TEST_MODULE IOLibTest

// Standard
#include <string>

// UtilsLib
#include <Mathematics.h>
#include <Vector3D.h>
#include <Vector.h>
#include <Test.h>
#include <Foreach.h>

// IOLib
#include <readEntity.h>

using namespace std;

TestCase( ReadEntityTest )
{
		string inputFile("../IOLibTest/input.txt");

		Entity entity1(5);

		Entity entity2 = readEntity(inputFile);


		checkEqual(entity1.getHandle(), entity2.getHandle());
		cout << entity1.getHandle() << " == " << entity2.getHandle() << " : " <<
			boolalpha << (entity1.getHandle() == entity2.getHandle()) << endl;

		check(false);
}
