#ifndef ELECTROSTATIC_FORCE_HPP
#define ELECTROSTATIC_FORCE_HPP

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle

struct ElectrostaticForce
{
	template<typename P1, typename P2>
	static void calculate(P1 particle1, P2 particle2)
	{
		double k = 9 * pow(10, 9);

		double charge1 = particle->get(electric_charge);
		double charge2 = neighbor->get(electric_charge);
		double r = particle->distance(neighbor);

		double force = - k * charge1 * charge2 / ( r * r );

		Vector3D electricForce = force * particle->normalDirection(neighbor);

		particle->addBodyForce( electricForce );
		neighbor->addBodyForce( - electricForce );
	}
};

#endif
