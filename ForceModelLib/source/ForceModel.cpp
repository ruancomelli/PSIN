#include "ForceModel.h"

// Normal Force Model
// Linear Dashpot Force
// Every comment in here may be related to the book Computational Granular Dynamics


/* taylorPredictor: Let f: A -> R^k be a function of class C^n, where A is in R. Let t be in A, and define
		currentVector = (f(t), f'(t), f''(t), ..., f^(n)(t))
		Given dt in R, Taylor theorem says that
		f(t + dt) = f(t) + dt * f'(t) + (1/2) * dt^2 * f''(t) + ... + (1/n!) * dt^n * f^(n)(t) + r(dt)	,
		where r is a function such that the limit of r(h) when h tends to zero is zero
		For a sufficiently small dt, we can approximate f(t+dt) by its expansion is Taylor's sum and writing r = 0
		The following function then calculates a new vector (f(t+dt), f'(t+dt), f''(t+dt), ..., f^(n)(t+dt)).
*/
DoubleVector2D ForceModel::taylorPredictor( DoubleVector2D currentVector, int predictionOrder, double dt ){
	// predictionOrder is the order of the derivatives to be computed.
	// dt is the time step for the predictionOrder
	// currentVector is a matrix of size predictionOrder X nDimensions, where nDimensions is the number of dimensions of the function to be predicted
	
	// This algorithm is an implementation of equation (2.24) (see reference) 
	
	DoubleVector2D predictedVector;
	DoubleVector taylorExpansion;
	
	int nDimensions = currentVector[0].size();
	
	// initialize predictedVector and taylorExpansion
	taylorExpansion.resize( nDimensions );
	predictedVector.resize( predictionOrder + 1 );
	
	for( int i = 0 ; i <= predictionOrder ; ++i ){
		predictedVector[i].resize( nDimensions );
	}
	
	// predict position
	for( int i = 0; i <= predictionOrder; ++i ){
		
		// set each entry of taylorExpansion to zero
		for( int j = 0 ; j < nDimensions ; ++j ){
			taylorExpansion[j] = 0;
		}
		
		// perform summation
		for( int j = i; j <= predictionOrder; ++j ){
			taylorExpansion += ( pow( dt , j - i) / factorial( j - i ) ) * currentVector[j];
		}
		
		// set the i-th predicted derivative as the calculated Taylor expansion
		predictedVector[i] = taylorExpansion;
		
	}

	return predictedVector;
}


DoubleVector2D ForceModel::gearCorrector(const DoubleVector2D & predictedVector, const DoubleVector & doubleDerivative, int predictionOrder, double dt){
	
	DoubleVector2D correctedVector = predictedVector;
	DoubleVector correctorConstants;
	
	switch(predictionOrder){
		case 3:
			setVector(correctorConstants, {1/6, 5/6, 1, 1/3}, predictionOrder + 1);
			break;
		case 4:
			setVector(correctorConstants, {19/90, 3/4, 1, 1/2, 1/12}, predictionOrder + 1);
			break;
		case 5:
			setVector(correctorConstants, {3/16, 251/360, 1, 11/18, 1/6, 1/60}, predictionOrder + 1);
			break;
		default:
			cout << endl << "There is no support for this prediction order" << endl << endl;
			return predictedVector;
	}
	
	for(int i = 0 ; i <= predictionOrder ; ++i){
		correctedVector[i] += (correctorConstants[i] * ( factorial(i) / pow(dt, i) ) * (pow(dt, 2) / 2) ) * doubleDerivative;
	}
	
	return correctedVector;
}

/*

DoubleVector ForceModel::linearDashpotForce(Particle particle1, Particle particle2, string method, string interaction ){
	// particle1 and particle2 are the particles between which the interaction must be calculated
	// mehtod specifies which discretization method must be used
	// method must be "Integral"
	// In the future, method should be able to be "FiniteDifference"
	// interaction specifies the kind of interaction that must be calculated
	// interaction must be "Impulse"
	// In the future, interaction should be able to be "Force"
	
	transform(interaction.begin(), interaction.end(), interaction.begin(), toupper);
	
	vector <double> normalInteraction;
	
	normalInteraction.resize(3);
	
	if (interaction.compare("IMPULSE") == 0)
		normalInteraction = linearDashpotForceImpulseCalculationViaIntegration(particle1, particle2, method);
	else if (interaction.compare("FORCE") == 0)
		normalInteraction = linearDashpotForceForceCalculationViaIntegration(particle1, particle2, method);

	return normalInteraction;
}

DoubleVector ForceModel::linearDashpotForceImpulseCalculationViaIntegration(Particle particle1, Particle particle2, string method){
	
}

DoubleVector linearDashpotForceForceCalculationViaIntegration(Particle particle1, Particle particle2, string method){

}

*/