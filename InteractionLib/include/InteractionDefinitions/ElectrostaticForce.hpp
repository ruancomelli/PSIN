#ifndef ELECTROSTATIC_FORCE_HPP
#define ELECTROSTATIC_FORCE_HPP

// PropertyLib
#include <PropertyDefinitions.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <mp/bool_constant.hpp>

namespace psin {

// ------------------ FORCE CALCULATION ------------------
//		particle is the reference
//		normalForce is the normal force applied BY neighbor TO particle
//		tangentialForce is the tangential force applied BY neighbor TO particle
struct ElectrostaticForce
{
	using ElectricCharge = PropertyDefinitions::ElectricCharge;

	template<typename P1, typename P2>
	struct check : mp::bool_constant<
		P1::template has_property<ElectricCharge>::value
		&& P2::template has_property<ElectricCharge>::value
		>
	{};

	template<typename P1, typename P2>
	constexpr static bool check_v = check<P1, P2>::value;

	template<typename P1, typename P2>
	static void calculate(P1 & particle, P2 & neighbor);
};

} // psin

#include <InteractionDefinitions/ElectrostaticForce.tpp>

#endif
