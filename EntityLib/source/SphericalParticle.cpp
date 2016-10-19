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

// ------------------------------- Geometric Parameter -------------------------------


void SphericalParticle::setGeometricParameter(const int geometricParameterIdentifier, const double geometricParameterValue)
{
	this->geometricParameter[geometricParameterIdentifier] = geometricParameterValue;
}

void SphericalParticle::setGeometricParameter(const DoubleVector geometricParameterVector)
{
	this->geometricParameter = geometricParameterVector;
}

double SphericalParticle::getGeometricParameter(const int geometricParameterIdentifier)
{
	return this->geometricParameter[geometricParameterIdentifier];
}

DoubleVector SphericalParticle::getGeometricParameter()
{
	return this->geometricParameter;
}

// ------------------------------- Collision detector -------------------------------

bool SphericalParticle::touch(SphericalParticle particle)
{
	return ( this->distance(particle) <= ( this->getGeometricParameter(RADIUS) + particle.getGeometricParameter(RADIUS) ) );
}


// ------------------------------- Auxiliar Functions -------------------------------

void SphericalParticle::reserveGeometricParameterMemory(void)
{
	this->geometricParameter.resize(N_GEOMETRIC_PARAMETER);
}