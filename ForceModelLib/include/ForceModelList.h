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
#include <StaticExecute.h>

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
#include <ForceModelSet.h>

using namespace std;

#include <ForceMethodsDefinitions.h>

STATIC_EXECUTE
{
	ForceModel viscoelasticSpheres("ViscoElasticSpheres");
	viscoelasticSpheres.setNormal( normalForceViscoelasticSpheres );
	viscoelasticSpheres.setTangential( tangentialForceHaffWerner );
	viscoelasticSpheres.requireProperty(mass);
	viscoelasticSpheres.requireProperty(elastic_modulus);
	viscoelasticSpheres.requireProperty(dissipative_constant);
	viscoelasticSpheres.requireProperty(poisson_ratio);
	viscoelasticSpheres.requireProperty(tangential_damping);
	viscoelasticSpheres.requireProperty(friction_parameter);

	forceModelSet.insert( viscoelasticSpheres );

	ForceModel electrostatic("Electrostatic");
	electrostatic.setField(electrostaticForce);
	electrostatic.setNormal( normalForceViscoelasticSpheres );
	electrostatic.setTangential( tangentialForceHaffWerner );
	electrostatic.requireProperty(mass);
	electrostatic.requireProperty(elastic_modulus);
	electrostatic.requireProperty(dissipative_constant);
	electrostatic.requireProperty(poisson_ratio);
	electrostatic.requireProperty(tangential_damping);
	electrostatic.requireProperty(friction_parameter);
	electrostatic.requireProperty(electric_charge);

	forceModelSet.insert( electrostatic );
}

#endif
