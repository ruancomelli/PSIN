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
		
		void addForce(DoubleVector force){ this->resultingForceDV += force; }
		void setResultingForce(DoubleVector force){ this->resultingForceDV = force; }
		DoubleVector getResultingForceDV(void) const { return this->resultingForceDV; }
		
		void addForce(const Vector3D & force){ this->resultingForce += force; }
		void setResultingForce(const Vector3D & force){ this->resultingForce = force; }
		Vector3D getResultingForce(void) const { return this->resultingForce; }
		
	private:
		DoubleVector resultingForceDV; //DV it to diferenciate them.
		Vector3D resultingForce;
		//DoubleVector2D interactionForce;
			// interaction force between this particle and all other particles and boundaries
}; // class Particle

#endif
