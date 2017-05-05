#ifndef PARTICLE_TPP
#define PARTICLE_TPP

// ------------------------------- Constructors -------------------------------
template<typename ... PropertyTypes>
Particle<PropertyTypes...>::Particle(const int handle, const int taylorOrder)
	: SocialEntity(handle),
	SpatialEntity(taylorOrder)
{
}

template<typename ... PropertyTypes>
Particle<PropertyTypes...>::Particle(const PhysicalEntity<PropertyDefinitions::Mass, PropertyDefinitions::MomentOfInertia, PropertyTypes...> & base, const int handle, const int taylorOrder)
	: PhysicalEntity<PropertyDefinitions::Mass, PropertyDefinitions::MomentOfInertia, PropertyTypes...>::PhysicalEntity(base),
	SocialEntity(handle),
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
	PropertyDefinitions::Mass myMass = PhysicalEntity<PhysicalEntity<PropertyDefinitions::Mass, PropertyDefinitions::MomentOfInertia, PropertyTypes...>>::template property<PropertyDefinitions::Mass>();
	double mass = this->property<PropertyDefinitions::Mass>().get();

	return mass * this->getVelocity();
}
template<typename ... PropertyTypes>
Vector3D Particle<PropertyTypes...>::getAngularMomentum() const
{
	double mass = this->property<PropertyDefinitions::Mass>().get();
	double momentOfInertia = this->property<PropertyDefinitions::MomentOfInertia>().get();

	return momentOfInertia * this->getAngularVelocity() +
			mass * cross( this->getPosition(), this->getVelocity() );
}

template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getTranslationalEnergy() const
{
	double mass = this->property<PropertyDefinitions::Mass>().get();

	return 0.5 * mass * this->getVelocity().squaredLength();
}
template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getRotationalEnergy() const
{
	double momentOfInertia = this->property<PropertyDefinitions::MomentOfInertia>().get();

	return 0.5 * momentOfInertia * this->getAngularVelocity().squaredLength();
}
template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getKineticEnergy() const
{
	return this->getTranslationalEnergy() + this->getRotationalEnergy();
}
template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getPotentialEnergy() const
{
	double mass = this->property<PropertyDefinitions::Mass>().get();

	return - mass * dot( this->getGravity(), this->getPosition() );
}
template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getMechanicalEnergy() const
{
	return this->getKineticEnergy() + this->getPotentialEnergy();
}

template<typename ... PropertyTypes>
void Particle<PropertyTypes...>::setGravity(const Vector3D & gravity)
{
	this->gravity = gravity;
}
template<typename ... PropertyTypes>
Vector3D Particle<PropertyTypes...>::getGravity() const 
{
	return this->gravity;
}	

#endif
