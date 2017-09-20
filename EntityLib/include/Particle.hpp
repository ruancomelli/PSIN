#ifndef PARTICLE_HPP
#define PARTICLE_HPP

// UtilsLib
#include <Named.hpp>
#include <string.hpp>

// EntityLib
#include <PhysicalEntity.hpp>
#include <SocialEntity.hpp>
#include <SpatialEntity.hpp>

// PropertyLib
#include <PropertyDefinitions.hpp>

namespace psin {

template<typename ... PropertyTypes>
class Particle :
	public Named,
	public PhysicalEntity<Mass, MomentOfInertia, PropertyTypes...>,
	public SpatialEntity
{
	using BasePhysicalEntity = PhysicalEntity<Mass, MomentOfInertia, PropertyTypes...>;

	public:	
		// ---- Constructors ----
		explicit Particle(const string & name = Named::defaultName, const int taylorOrder = DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
		explicit Particle(const BasePhysicalEntity & base, const string & name = Named::defaultName, const int taylorOrder = DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
		
		// ---- Dynamics ----
		void addBodyForce(const Vector3D & force);
		void addContactForce(const Vector3D & force);
		void setBodyForce(const Vector3D & force);
		void setContactForce(const Vector3D & force);

		Vector3D getBodyForce(void) const;
		Vector3D getContactForce(void) const;
		Vector3D getResultingForce(void) const;
		
		void addTorque(const Vector3D & torque);
		void setResultingTorque(const Vector3D & torque);
		Vector3D getResultingTorque(void) const;

		Vector3D getLinearMomentum(void) const;
		Vector3D getAngularMomentum(void) const;

		double getKineticEnergy(void) const;
		double getTranslationalEnergy(void) const;
		double getRotationalEnergy(void) const;
		double getPotentialEnergy(void) const;
		double getMechanicalEnergy(void) const;

		void setGravity(const Vector3D & gravity);
		Vector3D getGravity(void) const;	
		
	private:
		Vector3D bodyForce;
		Vector3D contactForce;

		Vector3D resultingTorque;

		static Vector3D gravity;
};

} // psin

#include <Particle.tpp>

#endif
