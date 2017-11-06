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
	public:	
		using BasePhysicalEntity = PhysicalEntity<Mass, MomentOfInertia, PropertyTypes...>;
		
		// ---- Constructors ----
		explicit Particle(const string & name = Named::defaultName, const int taylorOrder = DEFAULT_SPATIAL_ENTITY_TAYLOR_ORDER);
		explicit Particle(const BasePhysicalEntity & physical, const SpatialEntity & spatial = SpatialEntity(), const string & name = Named::defaultName);
		
		// ---- Dynamics ----
		void addBodyForce(const Vector3D & force);
		void addContactForce(const Vector3D & force);
		void setBodyForce(const Vector3D & force);
		void setContactForce(const Vector3D & force);

		template<typename NeighborType>
		void setNormalForce(NeighborType&& neighbor, const Vector3D & force);

		template<typename NeighborType>
		Vector3D getNormalForce(NeighborType&& neighbor) const;

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
		
	private:
		Vector3D bodyForce;
		Vector3D contactForce;

		Vector3D resultingTorque;

		std::map<string, Vector3D> normalForceMap;
};

template<typename...Prs>
void from_json(const json& j, Particle<Prs...> & p);
template<typename...Prs>
void to_json(json& j, const Particle<Prs...> & p);

} // psin

#include <Particle.tpp>

#endif
