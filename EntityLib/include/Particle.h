#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <vector>

#include <PhysicalEntity.h>

using namespace std;


class Particle: public PhysicalEntity
{
	public:
		Particle();
		Particle(const PhysicalEntity & base);
		Particle(const int taylorOrder, const int dimension, const int handle = -1);
		
		void addForce(Vector3D force){ this->resultingForce += force; }
		void setResultingForce(Vector3D force){ this->resultingForce = force; }
		Vector3D getResultingForce(void) const { return this->resultingForce; }
		
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
		Vector3D resultingForce;
		Vector3D resultingTorque;

		static Vector3D gravity;
		
		struct NeighborList{
			vector< Particle* > neighborPointer;
			vector< int > neighborHandle;
		};
		NeighborList neighborhood;
}; // class Particle

#endif
