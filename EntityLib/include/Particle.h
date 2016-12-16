#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <fstream>
#include <vector>

#include <PhysicalEntity.h>

using namespace std;


class Particle: public PhysicalEntity
{
	public:
		Particle();
		Particle(const PhysicalEntity & base);
		Particle(const int taylorOrder, const int dimension, const int handle = -1);
		
		void addBodyForce(Vector3D force){ this->bodyForce += force; }
		void addContactForce(Vector3D force){ this->contactForce += force; }
		void setBodyForce(Vector3D force){ this->bodyForce = force; }
		void setContactForce(Vector3D force){ this->contactForce = force; }

		Vector3D getBodyForce(void) const { return this->bodyForce; }
		Vector3D getContactForce(void) const { return this->contactForce; }
		Vector3D getResultingForce(void) const { return this->getBodyForce() + this->getContactForce(); }

		
		void addTorque(Vector3D torque){ this->resultingTorque += torque; }
		void setResultingTorque(Vector3D torque){ this->resultingTorque = torque; }
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
		vector< Particle* > getNeighborPointer(void){ return this->neighborhood.neighborPointer; }
		Particle* getNeighborPointerByIndex(int idx){ return this->neighborhood.neighborPointer[idx]; }
		vector< int > getNeighborHandle(void){ return this->neighborhood.neighborHandle; }
		int getNeighborHandleByIndex(int idx){ return this->neighborhood.neighborHandle[idx]; }

		void addNeighbor(Particle & neighbor);
		
	private:
		Vector3D bodyForce;
		Vector3D contactForce;

		Vector3D resultingTorque;

		static Vector3D gravity;
		
		struct NeighborList{
			vector< Particle* > neighborPointer;
			vector< int > neighborHandle;
		};
		NeighborList neighborhood;
}; // class Particle

#endif
