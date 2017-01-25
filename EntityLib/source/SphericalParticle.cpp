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

bool SphericalParticle::touches(SphericalParticlePtr particle)
{
	return ( this->distance(particle) <= ( this->getGeometricParameter(RADIUS) + particle->getGeometricParameter(RADIUS) ) );
}

Vector3D SphericalParticle::getNormalDirection(SphericalParticlePtr particle)
{
	Vector3D normalDirection = particle->getPosition(0) - this->getPosition(0);
	normalDirection.normalize();
	return normalDirection;
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
double SphericalParticle::distance(SphericalParticlePtr neighbor) const
{
	return this->getPosition(0).dist( neighbor->getPosition(0) );
}

// ------------------------------- Auxiliar Functions -------------------------------

void SphericalParticle::reserveGeometricParameterMemory(void)
{
	this->geometricParameter.resize(N_GEOMETRIC_PARAMETER);
}