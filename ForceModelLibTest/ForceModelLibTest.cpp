#include "ForceModel.h"

int main(int argc, char **argv){

	{// taylorPredictor test
		int predictionOrder = 3;
		vector<Vector3D> currentVector;
			currentVector.resize(predictionOrder);
			currentVector[0].x() = 0.0;
			currentVector[0].y() = 0.0;
			currentVector[0].z() = 0.0;
			currentVector[1].x() = 0.0;
			currentVector[1].y() = 0.0;
			currentVector[1].z() = 0.0;
			currentVector[2].x() = 0.0;
			currentVector[2].y() = 0.0;
			currentVector[2].z() = 0.0;
		double dt = 2;
		vector<Vector3D> vectorTaylorPredictor = ForceModel::taylorPredictor(currentVector, predictionOrder, dt );
	}
		
	{// viscoelasticSpheres test
		SphericalParticle particle1(3,3);
		SphericalParticle particle2(3,3);
		Vector3D vectorViscoelasticSphere = ForceModel::viscoelasticSpheres(particle1, particle2);
	}

	{// gearCorrector test
		int predictionOrder = 3;
		vector<Vector3D> predictedVector;
			predictedVector.resize(predictionOrder);
			predictedVector[0].x() = 0.0;
			predictedVector[0].y() = 0.0;
			predictedVector[0].z() = 0.0;
			predictedVector[1].x() = 0.0;
			predictedVector[1].y() = 0.0;
			predictedVector[1].z() = 0.0;
			predictedVector[2].x() = 0.0;
			predictedVector[2].y() = 0.0;
			predictedVector[2].z() = 0.0;
		Vector3D doubleDerivative(0., 0., 0.);
		double dt = 2;
	
		vector<Vector3D> vectorGearCorrector = ForceModel::gearCorrector(predictedVector, doubleDerivative, predictionOrder, dt);
	}

	return 0;
}
