#ifndef INTERACTION_TPP
#define INTERACTION_TPP

// #include <iostream>

namespace psin {
// template<typename InterfaceType, typename StoredType>
// void Interaction<SphericalParticle, SphericalParticle>::requireProperty( const Property<InterfaceType, StoredType> & property )
// {
// 	this->requiredProperties.insertProperty( property );
// }

template<typename T>
T Interaction<>::taylorPredictor( T&& currentVector, const std::size_t predictionOrder, const double dt )
{
	// predictionOrder is the order of the derivatives to be computed.
	// dt is the time step for the predictionOrder
	// currentVector is a matrix of size predictionOrder X nDimensions, where nDimensions is the number of dimensions of the function to be predicted

	// This algorithm is an implementation of equation (2.24) (see reference)

	T predictedVector( currentVector.size() );

	// predict position
	for( auto i = 0; i <= predictionOrder; ++i ){

		// perform summation
		for( auto j = i; j <= predictionOrder; ++j ){
			predictedVector[i] += ( pow( dt , j - i) / factorial( j - i ) ) * currentVector[j];
		}

	}

	return predictedVector;
}

template<typename T, typename U>
T Interaction<>::gearCorrector(T&& predictedVector, U&& doubleDerivative, const std::size_t predictionOrder, const double dt)
{
	// std::cout << "Starting gearCorrector" << std::endl; // DEBUG
	T correctedVector(predictionOrder + 1);
	vector<double> correctorConstants(predictionOrder + 1);

	switch(predictionOrder){
		case 3:
			correctorConstants[0] = 1./6.;
			correctorConstants[1] = 5./6.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 1./3.;
			break;
		case 4:
			correctorConstants[0] = 19./120.;
			correctorConstants[1] = 3./4.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 1./2.;
			correctorConstants[4] = 1./12.;
			break;
		case 5:
			correctorConstants[0] = 3./20.;
			correctorConstants[1] = 251./360.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 11./18.;
			correctorConstants[4] = 1./6.;
			correctorConstants[5] = 1./60.;
			break;
		case 6:
			correctorConstants[0] = 863./6048.;
			correctorConstants[1] = 665./1008.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 25./36.;
			correctorConstants[4] = 35./144.;
			correctorConstants[5] = 1./24.;
			correctorConstants[6] = 1./360.;
			break;
		case 7:
			correctorConstants[0] = 1925./14112.;
			correctorConstants[1] = 19087./30240.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 137./180.;
			correctorConstants[4] = 5./16.;
			correctorConstants[5] = 17./240.;
			correctorConstants[6] = 1./120.;
			correctorConstants[7] = 1./2520.;
			break;
		default:
			throw std::invalid_argument("There is no support for this prediction order. Prediction order must be either 3, 4, 5, 6 or 7.");
			return predictedVector;
	}

	// std::cout << "Applying correction" << std::endl; // DEBUG
	for(auto i = 0 ; i <= predictionOrder ; ++i){
		// std::cout << "i = " << i << std::endl; // DEBUG
		correctedVector[i] += (correctorConstants[i] * ( factorial(i) / pow(dt, i) ) * (pow(dt, 2) / 2.0) ) * (doubleDerivative - predictedVector[2]);
	}

	// std::cout << "Returning" << std::endl; // DEBUG
	return correctedVector;
}

} // psin

#endif
