#ifndef PARTICLE_HPP
#define PARTICLE_HPP

// Standard
#include <vector>

// EntityLib
#include <PhysicalEntity.hpp>

// UtilsLib
#include <SharedPointer.hpp>

class Particle: public PhysicalEntity
{
	public:	
		using ParticlePtr = SharedPointer< Particle >;

		// ---- Constructors ----
		Particle();
		explicit Particle(const PhysicalEntity & base);
		Particle(const int taylorOrder, const int dimension, const int handle = -1);
		
		// ---- Dynamics ----
		void addBodyForce(const Vector3D force){ this->bodyForce += force; }
		void addContactForce(const Vector3D force){ this->contactForce += force; }
		void setBodyForce(const Vector3D force){ this->bodyForce = force; } 
		void setContactForce(const Vector3D force){ this->contactForce = force; }

		Vector3D getBodyForce(void) const { return this->bodyForce; }
		Vector3D getContactForce(void) const { return this->contactForce; }
		Vector3D getResultingForce(void) const { return this->getBodyForce() + this->getContactForce(); }
		
		void addTorque(const Vector3D torque){ this->resultingTorque += torque; }
		void setResultingTorque(const Vector3D torque){ this->resultingTorque = torque; }
		Vector3D getResultingTorque(void) const { return this->resultingTorque; }

		Vector3D getLinearMomentum(void) const;
		Vector3D getAngularMomentum(void) const;

		double getKineticEnergy(void) const;
		double getTranslationalEnergy(void) const;
		double getRotationalEnergy(void) const;
		double getPotentialEnergy(void) const;
		double getMechanicalEnergy(void) const;

		void setGravity(Vector3D gravity){this->gravity = gravity;}
		Vector3D getGravity(void) const {return this->gravity;}
		
		
		// ---- Neighborhood ----
		void addNeighbor(ParticlePtr newNeighbor){ this->neighbor.push_back(newNeighbor->getHandle()); }
		void addNeighbor(int handle){ this->neighbor.push_back(handle); }
		int getNeighborHandleByIndex(int index){ return this->neighbor[index]; }
		vector<int> getNeighborhood(void){ return this->neighbor; }
		void setNeighborhoodSize(int size){ this->neighbor.resize(size); }
		
		
		// ---- Distance ----
		double distance(ParticlePtr particle);
		
	private:
		Vector3D bodyForce;
		Vector3D contactForce;

		Vector3D resultingTorque;
		
		vector<int> neighbor;

		static Vector3D gravity;
};

#endif
