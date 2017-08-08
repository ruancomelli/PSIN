#ifndef ELECTROSTATIC_FORCE_HPP
#define ELECTROSTATIC_FORCE_HPP

// PropertyLib
#include <PropertyDefinitions.hpp>

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle
struct ElectrostaticForce
{
	using ElectricCharge = PropertyDefinitions::ElectricCharge;

	template<typename P1, typename P2>
	static void calculate(P1 & particle, P2 & neighbor)
	{
		double k = 9e+9;

		double charge1 = particle.template get<ElectricCharge>();
		double charge2 = neighbor.template get<ElectricCharge>();
		double r = particle.distance(neighbor);

		double force = - k * charge1 * charge2 / ( r * r );

		Vector3D electricForce = force * particle.normalDirection(neighbor);

		particle.addBodyForce( electricForce );
		neighbor.addBodyForce( - electricForce );
	}
};

#endif
