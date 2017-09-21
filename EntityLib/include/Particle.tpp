#ifndef PARTICLE_TPP
#define PARTICLE_TPP

namespace psin {


// ------------------------------- Constructors -------------------------------
template<typename ... PropertyTypes>
Particle<PropertyTypes...>::Particle(const string & name, const int taylorOrder)
	: Named(name),
	SpatialEntity(taylorOrder)
{
}

template<typename ... PropertyTypes>
Particle<PropertyTypes...>::Particle(const BasePhysicalEntity & base, const string & name, const int taylorOrder)
	: BasePhysicalEntity(base),
	Named(name),
	SpatialEntity(taylorOrder)
{
}

// ------------------------------- Dynamics -------------------------------
template<typename ... PropertyTypes>
void Particle<PropertyTypes...>::addBodyForce(const Vector3D & force)
{ 
	this->bodyForce += force; 
}
template<typename ... PropertyTypes>
void Particle<PropertyTypes...>::addContactForce(const Vector3D & force)
{ 
	this->contactForce += force; 
}
template<typename ... PropertyTypes>
void Particle<PropertyTypes...>::setBodyForce(const Vector3D & force)
{ 
	this->bodyForce = force; 
} 
template<typename ... PropertyTypes>
void Particle<PropertyTypes...>::setContactForce(const Vector3D & force)
{ 
	this->contactForce = force; 
}

template<typename ... PropertyTypes>
Vector3D Particle<PropertyTypes...>::getBodyForce(void) const 
{ 
	return this->bodyForce; 
}
template<typename ... PropertyTypes>
Vector3D Particle<PropertyTypes...>::getContactForce(void) const 
{ 
	return this->contactForce; 
}
template<typename ... PropertyTypes>
Vector3D Particle<PropertyTypes...>::getResultingForce(void) const 
{ 
	return this->getBodyForce() + this->getContactForce(); 
}

template<typename ... PropertyTypes>		
void Particle<PropertyTypes...>::addTorque(const Vector3D & torque)
{ 
	this->resultingTorque += torque; 
}
template<typename ... PropertyTypes>
void Particle<PropertyTypes...>::setResultingTorque(const Vector3D & torque)
{ 
	this->resultingTorque = torque; 
}
template<typename ... PropertyTypes>
Vector3D Particle<PropertyTypes...>::getResultingTorque() const 
{ 
	return this->resultingTorque; 
}

template<typename ... PropertyTypes>
Vector3D Particle<PropertyTypes...>::getLinearMomentum() const
{
	

	double mass = this->template get<Mass>();

	return mass * this->getVelocity();
}
template<typename ... PropertyTypes>
Vector3D Particle<PropertyTypes...>::getAngularMomentum() const
{
	double mass = this->template get<Mass>();
	double momentOfInertia = this->template get<MomentOfInertia>();

	return momentOfInertia * this->getAngularVelocity() +
			mass * cross( this->getPosition(), this->getVelocity() );
}

template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getTranslationalEnergy() const
{
	double mass = this->template get<Mass>();

	return 0.5 * mass * this->getVelocity().squaredLength();
}

template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getRotationalEnergy() const
{
	double momentOfInertia = this->template get<MomentOfInertia>();

	return 0.5 * momentOfInertia * this->getAngularVelocity().squaredLength();
}

template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getKineticEnergy() const
{
	return this->getTranslationalEnergy() + this->getRotationalEnergy();
}

} // psin

#endif
