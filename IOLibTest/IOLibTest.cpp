
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

int main()
{
		string inputFile("../IOLibTest/input.txt");

		Entity entity1(5);

		Entity entity2 = readEntity(inputFile);

		cout << entity1.getHandle() << " == " << entity2.getHandle() << " : " <<
			boolalpha << (entity1.getHandle() == entity2.getHandle()) << endl;
}
