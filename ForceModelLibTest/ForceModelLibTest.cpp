#define BOOST_TEST_MODULE ForceModelLibTest

// UtilsLib
#include <Mathematics.h>
#include <Vector3D.h>
#include <Vector.h>
#include <Test.h>
#include <Foreach.h>

// PropertyLib
#include <PropertyContainer.h>
#include <PropertyList.h>

//EntityLib
#include <Entity.h>
#include <Particle.h>
#include <PhysicalEntity.h>
#include <SphericalParticle.h>

//ForceModelLib
#include <ForceModel.h>

using std::vector;

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

//	{// viscoelasticSpheres test
//		SphericalParticle particle1(3,3);
//		SphericalParticle particle2(3,3);
//		ForceModel::viscoelasticSpheres(particle1, particle2);
//	}

//	{// gearCorrector test
//		int predictionOrder = 3;
//		vector<Vector3D> predictedVector;
//			predictedVector.resize(predictionOrder);
//			predictedVector[0].x() = 0.0;
//			predictedVector[0].y() = 0.0;
//			predictedVector[0].z() = 0.0;
//			predictedVector[1].x() = 0.0;
//			predictedVector[1].y() = 0.0;
//			predictedVector[1].z() = 0.0;
//			predictedVector[2].x() = 0.0;
//			predictedVector[2].y() = 0.0;
//			predictedVector[2].z() = 0.0;
//		Vector3D doubleDerivative(0., 0., 0.);
//		double dt = 2;
//	
//		vector<Vector3D> vectorGearCorrector = ForceModel::gearCorrector(predictedVector, doubleDerivative, predictionOrder, dt);
//	}
