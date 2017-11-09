#ifndef INTERACTION_CPP
#define INTERACTION_CPP

#include <Interaction.hpp>

#include <iostream>

// Standard
#include <stdexcept>

// #include <Interaction.hpp>

// // PropertyLib
// #include <PropertyDefinitions.hpp>

// UtilsLib
#include <Mathematics.hpp>

namespace psin {

// using mass;
// using moment_of_inertia;

// using std::min;
// using std::max;


// Vector3D defaultNormalForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor )
// { 
// 	return nullVector3D(); 
// }

// void defaultTangentialForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep )
// {
// }

// void defaultFieldForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor )
// {
// }


// vector< vector< bool > > Interaction<SphericalParticle, SphericalParticle>::collisionFlag;
// int Interaction<SphericalParticle, SphericalParticle>::numberOfParticles;


// Interaction<SphericalParticle, SphericalParticle>::Interaction()
// 	: Named(),
// 	normalForceCalculationMethod( {defaultNormalForceCalculationMethod} ),
// 	tangentialForceCalculationMethod( {defaultTangentialForceCalculationMethod} ),
// 	fieldForceCalculationMethod( {defaultFieldForceCalculationMethod} )
// {
// }

// Interaction<SphericalParticle, SphericalParticle>::Interaction(const string & name)
// 	: Named(name),
// 	normalForceCalculationMethod( {defaultNormalForceCalculationMethod} ),
// 	tangentialForceCalculationMethod( {defaultTangentialForceCalculationMethod} ),
// 	fieldForceCalculationMethod( {defaultFieldForceCalculationMethod} )
// {
// }

// Interaction<SphericalParticle, SphericalParticle>::Interaction( const Interaction & fm )
// 	: Named( fm.getName() ),
// 	normalForceCalculationMethod( fm.normalForceCalculationMethod ),
// 	tangentialForceCalculationMethod( fm.tangentialForceCalculationMethod ),
// 	fieldForceCalculationMethod( fm.fieldForceCalculationMethod ),
// 	requiredProperties( fm.requiredProperties ),
// 	timeStep( fm.timeStep )
// {
// }

// void Interaction<SphericalParticle, SphericalParticle>::setNormal( NormalType newNormal ){	this->normalForceCalculationMethod = {newNormal}; }
// void Interaction<SphericalParticle, SphericalParticle>::setTangential( TangentialType newTangential ){	this->tangentialForceCalculationMethod = {newTangential}; }
// void Interaction<SphericalParticle, SphericalParticle>::setField( FieldType newField ){ this->fieldForceCalculationMethod = {newField}; }
// void Interaction<SphericalParticle, SphericalParticle>::setNormal( vector< NormalType > newNormal ){ this->normalForceCalculationMethod = newNormal; }
// void Interaction<SphericalParticle, SphericalParticle>::setTangential( vector< TangentialType > newTangential ){ this->tangentialForceCalculationMethod = newTangential; }
// void Interaction<SphericalParticle, SphericalParticle>::setField( vector< FieldType > newField ){ this->fieldForceCalculationMethod = newField; }
// void Interaction<SphericalParticle, SphericalParticle>::addNormal( NormalType newNormal ){ this->normalForceCalculationMethod.push_back( newNormal ); }
// void Interaction<SphericalParticle, SphericalParticle>::addTangential( TangentialType newTangential ){	this->tangentialForceCalculationMethod.push_back( newTangential ); }
// void Interaction<SphericalParticle, SphericalParticle>::addField( FieldType newField ){ this->fieldForceCalculationMethod.push_back( newField ); }


// void Interaction<SphericalParticle, SphericalParticle>::calculate( SphericalParticlePtr particle, SphericalParticlePtr neighbor )
// {
// 	Vector3D normalForce;

// 	for( auto& normalForceMethod : normalForceCalculationMethod )
// 	{
// 		normalForce += normalForceMethod( particle, neighbor );
// 	}

// 	for( auto& tangentialForceMethod : tangentialForceCalculationMethod )
// 	{
// 		tangentialForceMethod( particle, neighbor, normalForce, this->timeStep );
// 	}

// 	for( auto& fieldForceMethod : fieldForceCalculationMethod )
// 	{
// 		fieldForceMethod( particle, neighbor );
// 	}

// }

/* taylorPredictor: Let f: A -> R^k be a function of class C^n, where A is in R. Let t be in A, and define
		currentVector = (f(t), f'(t), f''(t), ..., f^(n)(t))
		Given dt in R, Taylor theorem says that
		f(t + dt) = f(t) + dt * f'(t) + (1/2) * dt^2 * f''(t) + ... + (1/n!) * dt^n * f^(n)(t) + r(dt)	,
		where r is a function such that the limit of r(h) when h tends to zero is zero
		For a sufficiently small dt, we can approximate f(t+dt) by its expansion in Taylor's sum and write r = 0
		The following function then calculates a new vector (f(t+dt), f'(t+dt), f''(t+dt), ..., f^(n)(t+dt)).
*/
std::vector<Vector3D> Interaction<>::taylorPredictor( const std::vector<Vector3D> & currentVector, const int predictionOrder, const double dt )
{
	// predictionOrder is the order of the derivatives to be computed.
	// dt is the time step for the predictionOrder
	// currentVector is a matrix of size predictionOrder X nDimensions, where nDimensions is the number of dimensions of the function to be predicted

	// This algorithm is an implementation of equation (2.24) (see reference)

	std::vector<Vector3D> predictedVector;
	Vector3D taylorExpansion;

	// initialize predictedVector and taylorExpansion
	predictedVector.resize( currentVector.size() );

	// predict position
	for( int i = 0; i <= predictionOrder; ++i ){

		// set each entry of taylorExpansion to zero
		taylorExpansion.x() = 0.0;
		taylorExpansion.y() = 0.0;
		taylorExpansion.z() = 0.0;

		// perform summation
		for( int j = i; j <= predictionOrder; ++j ){
			taylorExpansion += ( pow( dt , j - i) / factorial( j - i ) ) * currentVector[j];
		}

		// set the i-th predicted derivative as the calculated Taylor expansion
		predictedVector[i] = taylorExpansion;

	}

	return predictedVector;
}

std::vector<Vector3D> Interaction<>::gearCorrector(const std::vector<Vector3D> & predictedVector, const Vector3D & derivative, const int equationOrder, const int predictionOrder, const double dt)
{
	using std::vector;

	vector<Vector3D> correctedVector = predictedVector;
	vector<double> correctorConstants(predictionOrder + 1);

	switch(equationOrder)
	{
		case 1:
			switch(predictionOrder){
				case 2:
					correctorConstants[0] = 5./12.;
					correctorConstants[1] = 1;
					correctorConstants[2] = 1./2.;
					break;
				case 3:
					correctorConstants[0] = 3./8.;
					correctorConstants[1] = 1;
					correctorConstants[2] = 3./4.;
					correctorConstants[3] = 1./6.;
					break;
				case 4:
					correctorConstants[0] = 251./720.;
					correctorConstants[1] = 1;
					correctorConstants[2] = 11./12.;
					correctorConstants[3] = 1./3.;
					correctorConstants[4] = 1./24.;
					break;
				case 5:
					correctorConstants[0] = 95./288.;
					correctorConstants[1] = 1;
					correctorConstants[2] = 25./24.;
					correctorConstants[3] = 35./72.;
					correctorConstants[4] = 5./48.;
					correctorConstants[5] = 1./120.;
					break;
				case 6:
					correctorConstants[0] = 19087./60480.;
					correctorConstants[1] = 1;
					correctorConstants[2] = 137./120.;
					correctorConstants[3] = 5./8.;
					correctorConstants[4] = 17./96.;
					correctorConstants[5] = 1./40.;
					correctorConstants[6] = 1./720.;
					break;
				case 7:
					correctorConstants[0] = 5257./17280.;
					correctorConstants[1] = 1;
					correctorConstants[2] = 49./40.;
					correctorConstants[3] = 203./270.;
					correctorConstants[4] = 49./192.;
					correctorConstants[5] = 7./144.;
					correctorConstants[6] = 7./1440.;
					correctorConstants[7] = 1./5040.;
					break;
				default:
					throw std::invalid_argument("There is no support for this prediction order. Prediction order must be either 2, 3, 4, 5, 6 or 7.");
					return predictedVector;
			}
			break;
		case 2:
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
			break;
		default:
			throw std::invalid_argument("There is no support for this equation order. Equation order must be either 1 or 2.");
			return predictedVector;
	}

	for(int i = 0 ; i <= predictionOrder ; ++i){
		correctedVector[i] += (correctorConstants[i] * ( factorial(i) / pow(dt, i) ) * (pow(dt, equationOrder) / factorial(equationOrder)) ) * (derivative - predictedVector[equationOrder]);
	}

	return correctedVector;
}

// // Gear corrector
// void Interaction<SphericalParticle, SphericalParticle>::correctPosition( SphericalParticlePtr particle, const int predictionOrder, double dt )
// {
// 	vector<Vector3D> position = particle->getPosition();
// 	Vector3D acceleration = particle->getResultingForce() / particle->get( mass );
// 	vector<Vector3D> correctedPosition = gearCorrector( position, acceleration, predictionOrder, dt);
	
// 	particle->setPosition(correctedPosition);
// }

// void Interaction<SphericalParticle, SphericalParticle>::correctOrientation( SphericalParticlePtr particle, const int predictionOrder, double dt )
// {
// 	vector<Vector3D> orientation = particle->getOrientation();
// 	Vector3D angularAcceleration = particle->getResultingTorque() / particle->get( moment_of_inertia );
// 	vector<Vector3D> correctedOrientation = gearCorrector( orientation, angularAcceleration, predictionOrder, dt);
	
// 	particle->setOrientation(correctedOrientation);
// }

// void Interaction<SphericalParticle, SphericalParticle>::setNumberOfParticles( const int nParticles )
// {
// 	numberOfParticles = nParticles;
// 	resizeCollisionFlag(nParticles);
// }

// int Interaction<SphericalParticle, SphericalParticle>::getNumberOfParticles( void )
// {
// 	return Interaction::numberOfParticles;
// }

// void Interaction<SphericalParticle, SphericalParticle>::resizeCollisionFlag( const int numberOfParticles )
// {
// 	collisionFlag.resize( numberOfParticles - 1 );

// 	for( int i=0 ; i < (numberOfParticles - 1) ; ++i )
// 		collisionFlag[i].resize( numberOfParticles - 1 - i );
// }

// bool Interaction<SphericalParticle, SphericalParticle>::checkCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor )
// {
// 	const int index1 = min( particle->getHandle(), neighbor->getHandle() );
// 	const int index2 = max( particle->getHandle(), neighbor->getHandle() ) - index1 - 1;

// 	return collisionFlag[index1][index2];
// }

// void Interaction<SphericalParticle, SphericalParticle>::startCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor )
// {
// 	const int index1 = min( particle->getHandle(), neighbor->getHandle() );
// 	const int index2 = max( particle->getHandle(), neighbor->getHandle() ) - index1 - 1;

// 	collisionFlag[index1][index2] = true;
// }

// void Interaction<SphericalParticle, SphericalParticle>::endCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor )
// {
// 	const int index1 = min( particle->getHandle(), neighbor->getHandle() );
// 	const int index2 = max( particle->getHandle(), neighbor->getHandle() );

// 	collisionFlag[index1][index2 - index1 - 1] = false;
// }

// PropertyContainer Interaction<SphericalParticle, SphericalParticle>::getRequiredProperties(void)
// {
// 	return requiredProperties;
// }

// void Interaction<SphericalParticle, SphericalParticle>::setTimeStep( double timeStep )
// {
// 	this->timeStep = timeStep;
// }

} // psin

#endif