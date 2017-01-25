#include <Particle.h>

Vector3D Particle::gravity = nullVector3D();

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

Vector3D Particle::getLinearMomentum(void) const
{
		return this->getScalarProperty(MASS) * this->getPosition(1);
}

Vector3D Particle::getAngularMomentum(void) const
{
		return this->getScalarProperty(MOMENT_OF_INERTIA) * this->getOrientation(1) +
				getScalarProperty(MASS) * cross( this->getPosition(0), this->getPosition(1) );
}

double Particle::getTranslationalEnergy(void) const
{
	return 0.5 * this->getScalarProperty(MASS) * this->getPosition(1).squaredLength();
}

double Particle::getRotationalEnergy(void) const
{
	return 0.5 * this->getScalarProperty( MOMENT_OF_INERTIA ) * this->getOrientation(1).squaredLength();
}

double Particle::getKineticEnergy(void) const
{
	return this->getTranslationalEnergy() + this->getRotationalEnergy();
}

double Particle::getPotentialEnergy(void) const
{
	return - this->getScalarProperty(MASS) * dot( this->getGravity(), this->getPosition(0) );
}

double Particle::getMechanicalEnergy(void) const
{
	return this->getKineticEnergy() + this->getPotentialEnergy();
}