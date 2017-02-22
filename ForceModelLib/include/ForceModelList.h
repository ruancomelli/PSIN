#ifndef FORCE_MODEL_LIST_H
#define FORCE_MODEL_LIST_H

// std
#include <cmath>
#include <string>
#include <vector>
#include <ctype.h>
#include <stdexcept>

// UtilsLibSpecific
#include <Vector3D.h>
#include <Vector.h>
#include <Mathematics.h>
#include <SharedPointer.h>

// EntityLib
#include <Entity.h>
#include <PhysicalEntity.h>
#include <Particle.h>
#include <SphericalParticle.h>

// PropertyLib
#include <Property.h>
#include <PropertyList.h>
#include <PropertyContainer.h>

// ForceModel
#include <ForceModel.h>

using namespace std;

namespace ForceModelList
{
	vector< ForceModel > forceModelList;

	void addZeta( vector< vector< Vector3D > > & cummulativeZeta, const SphericalParticlePtr particle, const SphericalParticlePtr neighbor, const Vector3D zeta );
	void setZeta( vector< vector< Vector3D > > & cummulativeZeta, const SphericalParticlePtr particle, const SphericalParticlePtr neighbor, const Vector3D zeta );
	void resizeCummulativeZeta( vector< vector< Vector3D > > & cummulativeZeta, const int numberOfParticles );
			
	// Force calculation models
	Vector3D normalForceViscoelasticSpheres( SphericalParticlePtr particle, SphericalParticlePtr neighbor );
	Vector3D normalForceLinearDashpotForce( SphericalParticlePtr particle, SphericalParticlePtr neighbor );

	void tangentialForceHaffWerner( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep );
	void tangentialForceCundallStrack( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep );

	ForceModel viscoelasticSpheres("ViscoElasticSpheres");
	// viscoelasticSpheres.addNormal( normalForceViscoelasticSpheres );
	// viscoelasticSpheres.addTangential( tangentialForceHaffWerner );
	// forceModelList.push_back( viscoelasticSpheres );
};


#endif
