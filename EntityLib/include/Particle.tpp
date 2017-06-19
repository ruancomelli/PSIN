#ifndef PARTICLE_TPP
#define PARTICLE_TPP

template<typename ... PropertyTypes>
Vector3D Particle<PropertyTypes...>::gravity = nullVector3D();

// ------------------------------- Constructors -------------------------------
template<typename ... PropertyTypes>
Particle<PropertyTypes...>::Particle(const int handle, const int taylorOrder)
	: SocialEntity(handle),
	SpatialEntity(taylorOrder)
{
}

template<typename ... PropertyTypes>
Particle<PropertyTypes...>::Particle(const BasePhysicalEntity & base, const int handle, const int taylorOrder)
	: BasePhysicalEntity(base),
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
	using Mass = PropertyDefinitions::Mass;

	double mass = this->template get<Mass>();

	return mass * this->getVelocity();
}
template<typename ... PropertyTypes>
Vector3D Particle<PropertyTypes...>::getAngularMomentum() const
{
	using Mass = PropertyDefinitions::Mass;
	using MomentOfInertia = PropertyDefinitions::MomentOfInertia;

	double mass = this->template get<Mass>();
	double momentOfInertia = this->template get<MomentOfInertia>();

	return momentOfInertia * this->getAngularVelocity() +
			mass * cross( this->getPosition(), this->getVelocity() );
}

template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getTranslationalEnergy() const
{
	using Mass = PropertyDefinitions::Mass;
	
	double mass = this->template get<Mass>();

	return 0.5 * mass * this->getVelocity().squaredLength();
}
template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getRotationalEnergy() const
{
	using MomentOfInertia = PropertyDefinitions::MomentOfInertia;
	
	double momentOfInertia = this->template get<MomentOfInertia>();

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
	using Mass = PropertyDefinitions::Mass;
	
	double mass = this->template get<Mass>();

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
