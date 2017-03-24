#ifndef FORCE_METHODS_DEFINITIONS_H
#define FORCE_METHODS_DEFINITIONS_H

// EntityLib
#include <SphericalParticle.h>

// UtilsLib
#include <Vector3D.h>

// Standard
#include <vector>

void resizeCummulativeZeta( std::vector< std::vector< Vector3D > > & cummulativeZeta, const int numberOfParticles );
void addZeta( std::vector< std::vector< Vector3D > > & cummulativeZeta, const SphericalParticlePtr particle, const SphericalParticlePtr neighbor, const Vector3D zeta );
void setZeta( std::vector< std::vector< Vector3D > > & cummulativeZeta, const SphericalParticlePtr particle, const SphericalParticlePtr neighbor, const Vector3D zeta );

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle
// normalForceViscoelasticSpheres:
//		Calculates normal forces between two spherical particles according to equation (2.14) (see reference)
Vector3D normalForceViscoelasticSpheres( SphericalParticlePtr particle, SphericalParticlePtr neighbor);

// normalForceLinearDashpotForce:
//		Calculates normal forces between two spherical particles according to equation (2.8) (see reference)
Vector3D normalForceLinearDashpotForce( SphericalParticlePtr particle, SphericalParticlePtr neighbor );

//		tangentialForce is the tangential force applied BY neighbor TO particle
// tangentialForceHaffWerner:
//		Calculates tangential forces between two spherical particles according to equation (2.18) (see reference)
void tangentialForceHaffWerner( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep );

// tangentialForceCundallStrack:
//		Calculates tangential forces between two spherical particles according to equation (2.21) (see reference)
void tangentialForceCundallStrack( SphericalParticlePtr particle, SphericalParticlePtr neighbor, Vector3D normalForce, double timeStep );

void electrostaticForce( SphericalParticlePtr particle, SphericalParticlePtr neighbor );

#endif
