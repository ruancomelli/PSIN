#ifndef ELECTROSTATIC_FORCE_HPP
#define ELECTROSTATIC_FORCE_HPP

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle
struct ElectrostaticForce
{
	template<typename P1, typename P2>
	static void calculate(P1 & particle, P2 & neighbor);
};

#include <InteractionDefinitions/ElectrostaticForce.tpp>

#endif
