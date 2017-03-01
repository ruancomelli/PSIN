#ifndef FORCE_MODEL_LIST_H
#define FORCE_MODEL_LIST_H

// UtilsLib
#include <StaticExecute.h>

// PropertyLib
#include <PropertyList.h>

// ForceModel
#include <ForceModelSet.h>
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
