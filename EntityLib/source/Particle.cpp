#include <Particle.h>

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
		return this->getScalarProperty(MOMENT_OF_INERTIA) * this->getOrientation(1);
}

double Particle::getKineticEnergy(void) const
{
	return 0.5 * this->getScalarProperty(MASS) * this->getPosition(1).squaredLength();
}

double Particle::getRotationalEnergy(void) const
{
	return 0.5 * this->getScalarProperty( MOMENT_OF_INERTIA ) * this->getOrientation(1).squaredLength();
}

double Particle::getMechanicalEnergy(void) const
{
	return this->getKineticEnergy() + this->getRotationalEnergy();
}

void Particle::addNeighbor(Particle & neighbor){
	this->neighborhood.neighborPointer.push_back( &neighbor );
	this->neighborhood.neighborHandle.push_back( neighbor.getHandle() );
}