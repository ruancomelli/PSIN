#include <SphericalParticle.h>

// ------------------------------- Constructor -------------------------------
SphericalParticle::SphericalParticle()
	: Particle()
{
	reserveGeometricParameterMemory();
	
	setGeometry(SPHERE);
}

SphericalParticle::SphericalParticle(const int taylorOrder, const int dimension, const int handle)
	: Particle(taylorOrder, dimension, handle)
{
	setGeometry(SPHERE);
	
	// Initialize geometric parameter vector
	reserveGeometricParameterMemory();
}

SphericalParticle::SphericalParticle(const Particle & base)
	: Particle(base)
{
	setGeometry(SPHERE);
	reserveGeometricParameterMemory();
}
// ------------------------------- Geometric Parameter -------------------------------


void SphericalParticle::setGeometricParameter(const int geometricParameterIdentifier, const double geometricParameterValue)
{
	this->geometricParameter[geometricParameterIdentifier] = geometricParameterValue;
}

void SphericalParticle::setGeometricParameter(const DoubleVector geometricParameterVector)
{
	this->geometricParameter = geometricParameterVector;
}

double SphericalParticle::getGeometricParameter(const int geometricParameterIdentifier) const
{
	return this->geometricParameter[geometricParameterIdentifier];
}

DoubleVector SphericalParticle::getGeometricParameter() const
{
	return this->geometricParameter;
}

// ------------------------------- Collision detector -------------------------------

bool SphericalParticle::touches( const SphericalParticlePtr particle ) const
{
	return ( this->distance(particle) <= ( this->getGeometricParameter(RADIUS) + particle->getGeometricParameter(RADIUS) ) );
}

Vector3D SphericalParticle::contactPoint( const SphericalParticlePtr neighbor ) const
{
	if( this->touches( neighbor ) )
	{
		const double radius1 = this->getGeometricParameter( RADIUS );
		const double radius2 = neighbor->getGeometricParameter( RADIUS );

		const double distance = this->distance( neighbor );

		const double contactPointSize = ( (radius1*radius1) - (radius2*radius2) + (distance*distance) ) / ( 2 * distance );	// See law of cosines
		const Vector3D contactPoint = contactPointSize * this->normalDirection( neighbor ) + this->getPosition(0);

		return contactPoint;
	}

	return nullVector3D();
}

Vector3D SphericalParticle::normalDirection( const SphericalParticlePtr particle ) const
{
	Vector3D normalDirection = particle->getPosition(0) - this->getPosition(0);
	normalDirection.normalize();
	return normalDirection;
}

Vector3D SphericalParticle::relativeTangentialVelocity( const SphericalParticlePtr neighbor ) const
{
	const Vector3D normalVersor = this->normalDirection( neighbor );
	const Vector3D velocityDifference = neighbor->getPosition(1) - this->getPosition(1);
	const Vector3D contactPoint = this->contactPoint( neighbor );

	const Vector3D relativeTangentialCenterVelocity = velocityDifference - dot(velocityDifference, normalVersor) * normalVersor;
	const Vector3D relativeTangentialRotationalVelocity =	cross(neighbor->getOrientation(1), contactPoint - neighbor->getPosition(0)) -
															cross(this->getOrientation(1), contactPoint - this->getPosition(0));

	const Vector3D relativeTangentialVelocity = relativeTangentialCenterVelocity + relativeTangentialRotationalVelocity;

	return relativeTangentialVelocity;
}

Vector3D SphericalParticle::tangentialVersor( const SphericalParticlePtr neighbor ) const
{
	const Vector3D relativeTangentialVelocity = this->relativeTangentialVelocity( neighbor );

	return relativeTangentialVelocity.length() > 0 ?
								relativeTangentialVelocity / relativeTangentialVelocity.length() :
								nullVector3D();
}

// Spherical particles' overlap
double SphericalParticle::overlap( const SphericalParticlePtr neighbor ) const
{
	const double distance = this->distance( neighbor );
	const double radius1 = this->getGeometricParameter( RADIUS );
	const double radius2 = neighbor->getGeometricParameter( RADIUS );

	const double overlap = radius1 + radius2 - distance;
	return overlap;
}

double SphericalParticle::overlapDerivative( const SphericalParticlePtr neighbor ) const
{
	const Vector3D positionDifference = neighbor->getPosition(0) - this->getPosition(0);
	const Vector3D velocityDifference = neighbor->getPosition(1) - this->getPosition(1);

	const double overlapDerivative = - dot(positionDifference, velocityDifference) / positionDifference.length();

	return overlapDerivative;
}


// ------------------------------- Input and Output Functions -------------------------------
void SphericalParticle::fwritePosition( std::ostream & outFile, const string horizontalSeparator, const string verticalSeparator ){
	for( int i = 0 ; i <= this->getTaylorOrder() ; ++i ){
			outFile << horizontalSeparator << this->getPosition(i).x();
			outFile << horizontalSeparator << this->getPosition(i).y();
			outFile << horizontalSeparator << this->getPosition(i).z();
			outFile << verticalSeparator;
	}
}
		
// ------------------------------- Distance -------------------------------
double SphericalParticle::distance( const SphericalParticlePtr neighbor ) const
{
	return this->getPosition(0).dist( neighbor->getPosition(0) );
}

// ------------------------------- Auxiliar Functions -------------------------------

void SphericalParticle::reserveGeometricParameterMemory(void)
{
	this->geometricParameter.resize(N_GEOMETRIC_PARAMETER);
}