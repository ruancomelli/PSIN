#ifndef PARTICLE_TPP
#define PARTICLE_TPP

namespace psin {

template<typename...Prs>
void from_json(const json& j, Particle<Prs...> & p)
{
	Named named = j;
	typename Particle<Prs...>::BasePhysicalEntity physical = j;
	SpatialEntity spatial = j;

	p = Particle<Prs...>(physical, spatial, named.getName());

	if(j.count("bodyForce") > 0) p.setBodyForce(j.at("bodyForce"));
	if(j.count("contactForce") > 0) p.setContactForce(j.at("contactForce"));
	if(j.count("resultingTorque") > 0) p.setResultingTorque(j.at("resultingTorque"));
}

template<typename...Prs>
void to_json(json& j, const Particle<Prs...> & p)
{
	Named named = p;
	typename Particle<Prs...>::BasePhysicalEntity physical = p;
	SpatialEntity spatial = p;

	json jn = named;
	json jph = physical;
	json js = spatial;

	j = merge(merge(jn, jph), js);

	j["contactForce"] = p.getContactForce();
	j["contactForce - X"] = p.getContactForce().x();
	j["contactForce - Y"] = p.getContactForce().y();
	j["contactForce - Z"] = p.getContactForce().z();
	
	j["resultingForce"] = p.getResultingForce();
	j["resultingForce - X"] = p.getResultingForce().x();
	j["resultingForce - Y"] = p.getResultingForce().y();
	j["resultingForce - Z"] = p.getResultingForce().z();
	
	j["resultingTorque"] = p.getResultingTorque();
	j["resultingTorque - X"] = p.getResultingTorque().x();
	j["resultingTorque - Y"] = p.getResultingTorque().y();
	j["resultingTorque - Z"] = p.getResultingTorque().z();
	
	j["linearMomentum"] = p.getLinearMomentum();
	j["linearMomentum - X"] = p.getLinearMomentum().x();
	j["linearMomentum - Y"] = p.getLinearMomentum().y();
	j["linearMomentum - Z"] = p.getLinearMomentum().z();
	
	j["angularMomentum"] = p.getAngularMomentum();
	j["angularMomentum - X"] = p.getAngularMomentum().x();
	j["angularMomentum - Y"] = p.getAngularMomentum().y();
	j["angularMomentum - Z"] = p.getAngularMomentum().z();
	
	j["kineticEnergy"] = p.getKineticEnergy();
	j["translationalEnergy"] = p.getTranslationalEnergy();
	j["rotationalEnergy"] = p.getRotationalEnergy();
}

// ------------------------------- Constructors -------------------------------
template<typename ... PropertyTypes>
Particle<PropertyTypes...>::Particle(const string & name, const int taylorOrder)
	: Named(name),
	SpatialEntity(taylorOrder)
{
}

template<typename ... PropertyTypes>
Particle<PropertyTypes...>::Particle(const BasePhysicalEntity & physical, const SpatialEntity & spatial, const string & name)
	: BasePhysicalEntity(physical),
	SpatialEntity(spatial),
	Named(name)
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
template<typename NeighborType>
void Particle<PropertyTypes...>::setNormalForce(NeighborType&& neighbor, const Vector3D & force)
{ 
	this->normalForceMap[neighbor.getName()] = force;
}
template<typename ... PropertyTypes>
template<typename NeighborType>
Vector3D Particle<PropertyTypes...>::getNormalForce(NeighborType&& neighbor) const
{ 
	return this->normalForceMap.at(neighbor.getName());
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

	return 0.5 * mass * this->getVelocity().squaredNorm();
}

template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getRotationalEnergy() const
{	
	double momentOfInertia = this->template get<MomentOfInertia>();

	return 0.5 * momentOfInertia * this->getAngularVelocity().squaredNorm();
}

template<typename ... PropertyTypes>
double Particle<PropertyTypes...>::getKineticEnergy() const
{
	return this->getTranslationalEnergy() + this->getRotationalEnergy();
}

} // psin

#endif
