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
		
	private:
		Vector3D resultingForce;
}; // class Particle

#endif
