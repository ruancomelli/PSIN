#define BOOST_TEST_MODULE ForceModelLibTest

// UtilsLib
#include <Mathematics.h>
#include <Vector3D.h>
#include <Vector.h>
#include <Test.h>
#include <Foreach.h>

// PropertyLib
#include <PropertyContainer.h>
#include <PropertyDefinitions.h>

//EntityLib
#include <Entity.h>
#include <Particle.h>
#include <PhysicalEntity.h>
#include <SphericalParticle.h>

//ForceModelLib
#include <ForceModel.h>

// IOLib
#include <vectorIO.h>

using namespace std;
using PropertyDefinitions::mass;
using PropertyDefinitions::volume;

TestCase( TaylorPredictorTest )
{
		int predictionOrder = 2;
		double dx = 0.5;

		vector<Vector3D> currentVector(predictionOrder+1);
		currentVector[0].x() = 1.0;
		currentVector[1].x() = 3.0;
		currentVector[2].x() = 15.0;
		currentVector[0].y() = 4.0;
		currentVector[1].y() = -5.0;
		currentVector[2].y() = 8.0;
		currentVector[0].z() = -1.0;
		currentVector[1].z() = 2.0;
		currentVector[2].z() = -5.0;

		vector<Vector3D> solution(predictionOrder+1);
		solution[0].x() = 4.375;
		solution[1].x() = 10.5;
		solution[2].x() = 15.0;
		solution[0].y() = 2.5;
		solution[1].y() = -1.0;
		solution[2].y() = 8.0;
		solution[0].z() = -0.625;
		solution[1].z() = -0.5;
		solution[2].z() = -5.0;

		vector<Vector3D> predictedVector = ForceModel::taylorPredictor( currentVector, predictionOrder, dx );

		for(int i=0 ; i<=predictionOrder ; ++i)
		{
			for(int j=0 ; j<=predictionOrder ; ++j)
			{
				checkEqual( predictedVector[i].getComponent(j) , solution[i].getComponent(j) );
			}
		}
}

TestCase(RequirePropertiesTest)
{
	ForceModel fm;

	fm.requireProperty(mass);
	fm.requireProperty(volume);

	RawPropertyContainer raw = fm.getRequiredProperties();

	SharedPointer< set<string> > mySetPtr = raw.getPropertyNames();
	set<string>::iterator it = mySetPtr->find(mass.getName());
	set<string>::iterator it2 = mySetPtr->find(volume.getName());

	checkEqual(*it, mass.getName());
	checkEqual(*it2, volume.getName());
}

TestCase(ConstructorsTest)
{
	SphericalParticlePtr sph0( new SphericalParticle() );
	SphericalParticlePtr sph1( new SphericalParticle() );

	string defaultName = "Nameless";
	string name = "DarkSideOfTheForce";

	ForceModel fm0;
	fm0.calculate(sph0, sph1);
	checkEqual(fm0.getName(), defaultName);
	checkEqual(sph0->getResultingForce(), nullVector3D());
	checkEqual(sph1->getResultingForce(), nullVector3D());

	ForceModel fm1(name);
	fm1.calculate(sph0, sph1);
	checkEqual(fm1.getName(), name);
	checkEqual(sph0->getResultingForce(), nullVector3D());
	checkEqual(sph1->getResultingForce(), nullVector3D());

	ForceModel fm2(fm1);
	fm2.calculate(sph0, sph1);
	checkEqual(fm2.getName(), name);
	checkEqual(sph0->getResultingForce(), nullVector3D());
	checkEqual(sph1->getResultingForce(), nullVector3D());
}

Vector3D myNormalForce(SphericalParticlePtr sph0, SphericalParticlePtr sph1)
{
	sph0->addContactForce(Vector3D(1.0, 0.0, 0.0));
	sph1->addContactForce(Vector3D(1.0, 0.0, 0.0));
	return Vector3D(1.0, 0.0, 0.0);
}
void myTangentialForce(SphericalParticlePtr sph0, SphericalParticlePtr sph1, Vector3D normalForce, double timeStep)
{
	sph0->addContactForce(Vector3D(0.0, 1.0, 0.0));
	sph1->addContactForce(Vector3D(0.0, 1.0, 0.0));
}

TestCase(SetForceMethodsTest)
{
	SphericalParticlePtr sph0(new SphericalParticle());
	SphericalParticlePtr sph1(new SphericalParticle());
	SphericalParticlePtr sph2(new SphericalParticle());
	SphericalParticlePtr sph3(new SphericalParticle());
	SphericalParticlePtr sph4(new SphericalParticle());
	SphericalParticlePtr sph5(new SphericalParticle());

	string name = "DarkSideOfTheForce";

	Vector3D normalForce = Vector3D(1.0, 0.0, 0.0);
	Vector3D tangentialForce = Vector3D(0.0, 1.0, 0.0);


	ForceModel fm0(name);
	fm0.setNormal(myNormalForce);
	fm0.setTangential(myTangentialForce);
	fm0.calculate(sph0, sph1);
	checkEqual(fm0.getName(), name);
	checkEqual(sph0->getResultingForce(), normalForce + tangentialForce);
	checkEqual(sph1->getResultingForce(), normalForce + tangentialForce);

	ForceModel fm1(fm0);
	fm1.calculate(sph2, sph3);
	checkEqual(fm1.getName(), name);
	checkEqual(sph2->getResultingForce(), normalForce + tangentialForce);
	checkEqual(sph3->getResultingForce(), normalForce + tangentialForce);

	ForceModel fm2;
	fm2.setNormal({ myNormalForce, myNormalForce });
	fm2.setTangential(myTangentialForce);
	fm2.addTangential(myTangentialForce);
	fm2.calculate(sph4, sph5);
	checkEqual(sph4->getResultingForce(), 2*normalForce + 2*tangentialForce);
	checkEqual(sph5->getResultingForce(), 2*normalForce + 2*tangentialForce);
}

void myTangentialForce2(SphericalParticlePtr sph0, SphericalParticlePtr sph1, Vector3D normalForce, double timeStep)
{
	sph0->addContactForce( timeStep * Vector3D(0.0, 1.0, 0.0) );
}

TestCase(SetTimeStepAndNumberOfParticlesTest)
{
	SphericalParticlePtr sph0(new SphericalParticle());
	SphericalParticlePtr sph1(new SphericalParticle());

	ForceModel fm;
	int numberOfParticles = 100;
	double timeStep = 0.8;

	fm.setNumberOfParticles(numberOfParticles);
	checkEqual(fm.getNumberOfParticles(), numberOfParticles);

	fm.setTimeStep(timeStep);
	auto tangentialForce = timeStep * Vector3D(0.0, 1.0, 0.0);

	fm.setTangential(myTangentialForce2);
	fm.calculate(sph0, sph1);
	checkEqual(sph0->getResultingForce(), tangentialForce);
}
