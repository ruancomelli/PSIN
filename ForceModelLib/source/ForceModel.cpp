#include <ForceModel.h>

// PropertyLib
#include <PropertyList.h>

// UtilsLib
#include <Mathematics.h>



using PropertyList::mass;
using PropertyList::moment_of_inertia;



Vector3D defaultNormalForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor )
{ 
	return nullVector3D(); 
}

void defaultTangentialForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep )
{
}

void defaultFieldForceCalculationMethod( SphericalParticlePtr particle, SphericalParticlePtr neighbor )
{
}


vector< vector< bool > > ForceModel::collisionFlag;
int ForceModel::numberOfParticles;


ForceModel::ForceModel()
	: name("Nameless"),
	normalForceCalculationMethod( {defaultNormalForceCalculationMethod} ),
	tangentialForceCalculationMethod( {defaultTangentialForceCalculationMethod} ),
	fieldForceCalculationMethod( {defaultFieldForceCalculationMethod} )
{
}

ForceModel::ForceModel(const string & name)
	: name(name),
	normalForceCalculationMethod( {defaultNormalForceCalculationMethod} ),
	tangentialForceCalculationMethod( {defaultTangentialForceCalculationMethod} ),
	fieldForceCalculationMethod( {defaultFieldForceCalculationMethod} )
{
}

ForceModel::ForceModel( const ForceModel & fm )
	: name( fm.name ),
	normalForceCalculationMethod( fm.normalForceCalculationMethod ),
	tangentialForceCalculationMethod( fm.tangentialForceCalculationMethod ),
	fieldForceCalculationMethod( fm.fieldForceCalculationMethod ),
	requiredProperties( fm.requiredProperties ),
	timeStep( fm.timeStep )
{
}

void ForceModel::setNormal( NormalType newNormal ){	this->normalForceCalculationMethod = {newNormal}; }
void ForceModel::setTangential( TangentialType newTangential ){	this->tangentialForceCalculationMethod = {newTangential}; }
void ForceModel::setField( FieldType newField ){ this->fieldForceCalculationMethod = {newField}; }
void ForceModel::setNormal( vector< NormalType > newNormal ){ this->normalForceCalculationMethod = newNormal; }
void ForceModel::setTangential( vector< TangentialType > newTangential ){ this->tangentialForceCalculationMethod = newTangential; }
void ForceModel::setField( vector< FieldType > newField ){ this->fieldForceCalculationMethod = newField; }
void ForceModel::addNormal( NormalType newNormal ){ this->normalForceCalculationMethod.push_back( newNormal ); }
void ForceModel::addTangential( TangentialType newTangential ){	this->tangentialForceCalculationMethod.push_back( newTangential ); }
void ForceModel::addField( FieldType newField ){ this->fieldForceCalculationMethod.push_back( newField ); }


void ForceModel::calculate( SphericalParticlePtr particle, SphericalParticlePtr neighbor )
{
	Vector3D normalForce;

	for( auto& normalForceMethod : normalForceCalculationMethod )
	{
		normalForce += normalForceMethod( particle, neighbor );
	}

	for( auto& tangentialForceMethod : tangentialForceCalculationMethod )
	{
		tangentialForceMethod( particle, neighbor, normalForce, this->timeStep );
	}

	for( auto& fieldForceMethod : fieldForceCalculationMethod )
	{
		fieldForceMethod( particle, neighbor );
	}

}

/* taylorPredictor: Let f: A -> R^k be a function of class C^n, where A is in R. Let t be in A, and define
		currentVector = (f(t), f'(t), f''(t), ..., f^(n)(t))
		Given dt in R, Taylor theorem says that
		f(t + dt) = f(t) + dt * f'(t) + (1/2) * dt^2 * f''(t) + ... + (1/n!) * dt^n * f^(n)(t) + r(dt)	,
		where r is a function such that the limit of r(h) when h tends to zero is zero
		For a sufficiently small dt, we can approximate f(t+dt) by its expansion in Taylor's sum and write r = 0
		The following function then calculates a new vector (f(t+dt), f'(t+dt), f''(t+dt), ..., f^(n)(t+dt)).
*/
vector<Vector3D> ForceModel::taylorPredictor( const vector<Vector3D> & currentVector, const int predictionOrder, const double dt )
{
	// predictionOrder is the order of the derivatives to be computed.
	// dt is the time step for the predictionOrder
	// currentVector is a matrix of size predictionOrder X nDimensions, where nDimensions is the number of dimensions of the function to be predicted

	// This algorithm is an implementation of equation (2.24) (see reference)

	vector<Vector3D> predictedVector;
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

vector<Vector3D> ForceModel::gearCorrector(const vector<Vector3D> & predictedVector, const Vector3D & doubleDerivative, const int predictionOrder, const double dt){

	vector<Vector3D> correctedVector = predictedVector;
	DoubleVector correctorConstants(predictionOrder + 1);

	switch(predictionOrder){
		case 3:
			correctorConstants[0] = 1./6.;
			correctorConstants[1] = 5./6.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 1./3.;
			break;
		case 4:
			correctorConstants[0] = 19./90.;
			correctorConstants[1] = 3./4.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 1./2.;
			correctorConstants[4] = 1./12.;
			break;
		case 5:
			correctorConstants[0] = 3./16.;
			correctorConstants[1] = 251./360.;
			correctorConstants[2] = 1.;
			correctorConstants[3] = 11./18.;
			correctorConstants[4] = 1./6.;
			correctorConstants[5] = 1./60.;
			break;
		default:
			throw runtime_error("There is no support for this prediction order. Prediction order must be either 3, 4 or 5.");
			return predictedVector;
	}

	for(int i = 0 ; i <= predictionOrder ; ++i){
		correctedVector[i] += (correctorConstants[i] * ( factorial(i) / pow(dt, i) ) * (pow(dt, 2) / 2.0) ) * (doubleDerivative - predictedVector[2]);
	}

	return correctedVector;
}

// Gear corrector
void ForceModel::correctPosition( SphericalParticlePtr particle, const int predictionOrder, double dt )
{
	vector<Vector3D> position = particle->getPosition();
	Vector3D acceleration = particle->getResultingForce() / particle->get( mass );
	vector<Vector3D> correctedPosition = gearCorrector( position, acceleration, predictionOrder, dt);
	
	particle->setPosition(correctedPosition);
}

void ForceModel::correctOrientation( SphericalParticlePtr particle, const int predictionOrder, double dt )
{
	vector<Vector3D> orientation = particle->getOrientation();
	Vector3D angularAcceleration = particle->getResultingTorque() / particle->get( moment_of_inertia );
	vector<Vector3D> correctedOrientation = gearCorrector( orientation, angularAcceleration, predictionOrder, dt);
	
	particle->setOrientation(correctedOrientation);
}

string ForceModel::getName(void) const
{ 
	return this->name; 
}

void ForceModel::setName(const string & name)
{ 
	this->name = name;
}

void ForceModel::setNumberOfParticles( const int nParticles )
{
	numberOfParticles = nParticles;
	resizeCollisionFlag(nParticles);
}

int ForceModel::getNumberOfParticles( void )
{
	return ForceModel::numberOfParticles;
}

void ForceModel::resizeCollisionFlag( const int numberOfParticles )
{
	collisionFlag.resize( numberOfParticles - 1 );

	for( int i=0 ; i < (numberOfParticles - 1) ; ++i )
		collisionFlag[i].resize( numberOfParticles - 1 - i );
}

bool ForceModel::checkCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor )
{
	const int index1 = min( particle->getHandle(), neighbor->getHandle() );
	const int index2 = max( particle->getHandle(), neighbor->getHandle() ) - index1 - 1;

	return collisionFlag[index1][index2];
}

void ForceModel::startCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor )
{
	const int index1 = min( particle->getHandle(), neighbor->getHandle() );
	const int index2 = max( particle->getHandle(), neighbor->getHandle() ) - index1 - 1;

	collisionFlag[index1][index2] = true;
}

void ForceModel::endCollision( const SphericalParticlePtr particle, const SphericalParticlePtr neighbor )
{
	const int index1 = min( particle->getHandle(), neighbor->getHandle() );
	const int index2 = max( particle->getHandle(), neighbor->getHandle() );

	collisionFlag[index1][index2 - index1 - 1] = false;
}

RawPropertyContainer ForceModel::getRequiredProperties(void)
{
	return requiredProperties;
}

void ForceModel::setTimeStep( double timeStep )
{
	this->timeStep = timeStep;
}