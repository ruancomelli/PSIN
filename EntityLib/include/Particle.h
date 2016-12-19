#ifndef PARTICLE_H
#define PARTICLE_H

// Standard
#include <iostream>
#include <fstream>
#include <vector>

// EntityLib
#include <PhysicalEntity.h>

// boost
#include <SharedPointer.h>

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
		void addNeighbor(Particle & neighbor){ this->neighbor.push_back(neighbor.getHandle()); }
		void addNeighbor(int handle){ this->neighbor.push_back(handle); }
		int getNeighborHandleByIndex(int index){ return this->neighbor[index]; }
		vector<int> getNeighborhood(void){ return this->neighbor; }
		void setNeighborhoodSize(int size){ this->neighbor.resize(size); }
		
	private:
		Vector3D bodyForce;
		Vector3D contactForce;

		Vector3D resultingTorque;

		static Vector3D gravity;
		
		vector<int> neighbor;
}; // class Particle

typedef SharedPointer< Particle > ParticlePtr;

#endif
