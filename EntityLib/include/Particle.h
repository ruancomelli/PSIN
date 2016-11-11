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
		Particle(const int taylorOrder, const int dimension, const int handle = -1);
		//Particle(const int taylorOrder, const int handle = -1);
		
		void addForce(Vector3D force){ this->resultingForce += force; }
		void setResultingForce(Vector3D force){ this->resultingForce = force; }
		Vector3D getResultingForce(void) const { return this->resultingForce; }
		
		void addTorque(Vector3D torque){ this->resultingTorque += torque; }
		void setResultingTorque(Vector3D torque){ this->resultingTorque = torque; }
		Vector3D getResultingTorque(void) const { return this->resultingTorque; }
		
		
		// ---- Neighborhood ----
		vector< Particle* > getNeighborPointer(void){ return this->neighbor.neighborPointer; }
		Particle* getNeighborPointerByIndex(int idx){ return this->neighbor.neighborPointer[idx]; }
		vector< int > getNeighborHandle(void){ return this->neighbor.neighborHandle; }
		int getNeighborHandleByIndex(int idx){ return this->neighbor.neighborHandle[idx]; }
		
	private:
		Vector3D resultingForce;
		Vector3D resultingTorque;
		
		struct neighborList{
			vector< Particle* > neighborPointer;
			vector< int > neighborHandle;
		};
		neighborList neighbor;
}; // class Particle

#endif
