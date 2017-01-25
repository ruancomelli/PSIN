#include <ForceModel.h>

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
vector<Vector3D> ForceModel::taylorPredictor( const vector<Vector3D> & currentVector, const int predictionOrder, const double dt ){
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
			throw runtime_error("There is no support for this prediction order");
			return predictedVector;
	}

	for(int i = 0 ; i <= predictionOrder ; ++i){
		correctedVector[i] += (correctorConstants[i] * ( factorial(i) / pow(dt, i) ) * (pow(dt, 2) / 2.0) ) * (doubleDerivative - predictedVector[2]);
	}

	return correctedVector;
}

// viscoelasticSpheres:
//		Calculates normal and tangential forces between two spherical particles according to equation (2.14) (see reference)
//		normalForce is the normal force applied BY particle2 TO particle1
//		tangentialForce is the tangential force applied BY particle2 TO particle1
void ForceModel::viscoelasticSpheres( SphericalParticlePtr particle1,  SphericalParticlePtr particle2)
{	
	Vector3D force;

	// Getting particles properties and parameters
	const Vector3D position1 = particle1->getPosition(0);
	const Vector3D position2 = particle2->getPosition(0);
	const double distance = position1.dist(position2);
	const double radius1 = particle1->getGeometricParameter(RADIUS);
	const double radius2 = particle2->getGeometricParameter(RADIUS);
	
	// Calculations
	const double overlap = radius1 + radius2 - distance;
	
	if(overlap > 0)
	{
		const Vector3D velocity1 = particle1->getPosition( 1 );
		const Vector3D velocity2 = particle2->getPosition( 1 );
		
		const Vector3D positionDifference = position2 - position1;
		const Vector3D velocityDifference = velocity2 - velocity1;
		
		const Vector3D normalVersor = positionDifference / positionDifference.length();
		
		const Vector3D angularVelocity1 = particle1->getOrientation( 1 );
		const Vector3D angularVelocity2 = particle2->getOrientation( 1 );
		
		// Get physical properties and calculate effective parameters
		const double effectiveRadius = radius1 * radius2 / ( radius1 + radius2 );
		
		const double elasticModulus1 = particle1->getScalarProperty( ELASTIC_MODULUS );
		const double elasticModulus2 = particle2->getScalarProperty( ELASTIC_MODULUS );
		
		const double dissipativeConstant1 = particle1->getScalarProperty( DISSIPATIVE_CONSTANT );
		const double dissipativeConstant2 = particle2->getScalarProperty( DISSIPATIVE_CONSTANT );
		
		
		const double poissonRatio1 = particle1->getScalarProperty( POISSON_RATIO );
		const double poissonRatio2 = particle2->getScalarProperty( POISSON_RATIO );

		const double tangentialDamping1 = particle1->getScalarProperty( TANGENTIAL_DAMPING );
		const double tangentialDamping2 = particle2->getScalarProperty( TANGENTIAL_DAMPING );
		const double effectiveTangentialDamping = min( tangentialDamping1 , tangentialDamping2 );
			
		const double frictionParameter1 = particle1->getScalarProperty( FRICTION_PARAMETER );
		const double frictionParameter2 = particle2->getScalarProperty( FRICTION_PARAMETER );
		const double effectiveFrictionParameter = min( frictionParameter1, frictionParameter2 );
		
		
		// Calculate normal force
		const double overlapDerivative = - dot(positionDifference, velocityDifference) / positionDifference.length();
		const double term1 = (4/3) * sqrt(effectiveRadius);
		const double term2 = sqrt(overlap) * (overlap + 0.5 * (dissipativeConstant1 + dissipativeConstant2) * overlapDerivative );
		const double term3 = (1 - poissonRatio1*poissonRatio1)/elasticModulus1 + (1 - poissonRatio2*poissonRatio2)/elasticModulus2;
		
		const double normalForceModulus = max( term1 * term2 / term3 , 0.0 );
		
		const Vector3D normalForce = - normalForceModulus * normalVersor;
		
		particle1->addContactForce( normalForce );
		particle2->addContactForce( - normalForce );
		
		// Calculate tangential force
		const double contactPointSize = ( (radius1*radius1) - (radius2*radius2) + positionDifference.squaredLength() ) / ( 2 * positionDifference.length() );	// See law of cosines
		const Vector3D contactPoint = contactPointSize * normalVersor + position1;
		
		const Vector3D relativeTangentialCenterVelocity = velocityDifference - dot(velocityDifference, normalVersor) * normalVersor;
		const Vector3D relativeTangentialRotationalVelocity =	cross(angularVelocity2, contactPoint - position2) -
														cross(angularVelocity1, contactPoint - position1);
		
		const Vector3D relativeTangentialVelocity = relativeTangentialCenterVelocity + relativeTangentialRotationalVelocity;
		
		const Vector3D tangentialVersor = relativeTangentialVelocity.length() > 0 ?
									relativeTangentialVelocity / relativeTangentialVelocity.length() :
									nullVector3D();
		
		const Vector3D tangentialForce =	min( effectiveTangentialDamping * relativeTangentialVelocity.length() , 
			effectiveFrictionParameter * abs(normalForceModulus) ) * tangentialVersor;
		
		particle1->addContactForce( tangentialForce );
		particle2->addContactForce( - tangentialForce );
									
		particle1->addTorque( cross(contactPoint - position1, tangentialForce) );
		particle2->addTorque( cross(contactPoint - position2, - tangentialForce) );
	}
	// else, no forces and no torques are added.
}



void ForceModel::correctPosition( SphericalParticlePtr particle, const int predictionOrder, double dt )
{
	vector<Vector3D> position = particle->getPosition();
	Vector3D acceleration = particle->getResultingForce() / particle->getScalarProperty( MASS );
	vector<Vector3D> correctedPosition = gearCorrector( position, acceleration, predictionOrder, dt);
	
	particle->setPosition(correctedPosition);
}

void ForceModel::correctOrientation( SphericalParticlePtr particle, const int predictionOrder, double dt )
{
	vector<Vector3D> orientation = particle->getOrientation();
	Vector3D angularAcceleration = particle->getResultingTorque() / particle->getScalarProperty( MOMENT_OF_INERTIA );
	vector<Vector3D> correctedOrientation = gearCorrector( orientation, angularAcceleration, predictionOrder, dt);
	
	particle->setOrientation(correctedOrientation);
}

void ForceModel::linearDashpotForce( SphericalParticlePtr particle1, SphericalParticlePtr particle2 ){
	/* TO BE IMPLEMENTED */
}