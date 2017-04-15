#include <Particle.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

using PropertyDefinitions::mass;
using PropertyDefinitions::moment_of_inertia;

Vector3D Particle::gravity = nullVector3D();

// ------------------------------- Constructors -------------------------------
Particle::Particle() : PhysicalEntity(3, 3) 
{
}

Particle::Particle( const PhysicalEntity & base )
	: PhysicalEntity( base )
{
}

Particle::Particle(const int taylorOrder, const int dimension, const int handle)
	: PhysicalEntity(taylorOrder, dimension, handle)
{
}

// ------------------------------- Dynamics -------------------------------
Vector3D Particle::getLinearMomentum(void) const
{
		return this->get(mass) * this->getPosition(1);
}

Vector3D Particle::getAngularMomentum(void) const
{
		return this->get(moment_of_inertia) * this->getOrientation(1) +
				get(mass) * cross( this->getPosition(0), this->getPosition(1) );
}

double Particle::getTranslationalEnergy(void) const
{
	return 0.5 * this->get(mass) * this->getPosition(1).squaredLength();
}

double Particle::getRotationalEnergy(void) const
{
	return 0.5 * this->get( moment_of_inertia ) * this->getOrientation(1).squaredLength();
}

double Particle::getKineticEnergy(void) const
{
	return this->getTranslationalEnergy() + this->getRotationalEnergy();
}

double Particle::getPotentialEnergy(void) const
{
	return - this->get(mass) * dot( this->getGravity(), this->getPosition(0) );
}

double Particle::getMechanicalEnergy(void) const
{
	return this->getKineticEnergy() + this->getPotentialEnergy();
}

// ------------------------------- Distance -------------------------------
double Particle::distance(ParticlePtr particle){
	return this->getPosition(0).dist( particle->getPosition(0) );
}