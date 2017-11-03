#ifndef ELECTROSTATIC_FORCE_TPP
#define ELECTROSTATIC_FORCE_TPP

// PropertyLib
#include <PropertyDefinitions.hpp>

// UtilsLib
#include <Vector3D.hpp>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle
template<typename P1, typename P2, typename T>
void ElectrostaticForce::calculate(P1 & particle, P2 & neighbor, const T &)
{
	double k = 9e+9;

	double charge1 = particle.template get<ElectricCharge>();
	double charge2 = neighbor.template get<ElectricCharge>();
	double r = distance(particle, neighbor);

	double force = - k * charge1 * charge2 / ( r * r );

	Vector3D electricForce = force * normalVersor(particle, neighbor);

	particle.addBodyForce( electricForce );
	neighbor.addBodyForce( - electricForce );
}

} // psin


#endif
