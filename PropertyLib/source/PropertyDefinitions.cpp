#include <PropertyDefinitions.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <string.hpp>

// Standard
#include <iostream>

namespace psin {
	
// ========================================== MASS ==========================================
template<> const string NamedType<Mass>::name = "Mass";
Mass Builder<Mass>::build(const json& j)
{
	Mass x;
	x.set( j );
	return x;
}

// ========================================== VOLUME ==========================================
template<> const string NamedType<Volume>::name = "Volume";
Volume Builder<Volume>::build(const json& j)
{
	Volume x;
	x.set( j );
	return x;
}

// ========================================== MOMENT OF INERTIA ==========================================
template<> const string NamedType<MomentOfInertia>::name = "MomentOfInertia";
MomentOfInertia Builder<MomentOfInertia>::build(const json& j)
{
	MomentOfInertia x;
	x.set( j );
	return x;
}

// ========================================== MOMENT OF INERTIA ==========================================
template<> const string NamedType<Radius>::name = "Radius";
Radius Builder<Radius>::build(const json& j)
{
	Radius x;
	x.set( j );
	return x;
}

// ========================================== ELASTIC MODULUS ==========================================
template<> const string NamedType<ElasticModulus>::name = "ElasticModulus";
ElasticModulus Builder<ElasticModulus>::build(const json& j)
{
	ElasticModulus x;
	x.set( j );
	return x;
}

// ========================================== DISSIPATIVE CONSTANT ==========================================
template<> const string NamedType<DissipativeConstant>::name = "DissipativeConstant";
DissipativeConstant Builder<DissipativeConstant>::build(const json& j)
{
	DissipativeConstant x;
	x.set( j );
	return x;
}

// ========================================== POISSON RATIO ==========================================
template<> const string NamedType<PoissonRatio>::name = "PoissonRatio";
PoissonRatio Builder<PoissonRatio>::build(const json& j)
{
	PoissonRatio x;
	x.set( j );
	return x;
}

// ========================================== NORMAL DISSIPATIVE CONSTANT ==========================================
template<> const string NamedType<NormalDissipativeConstant>::name = "NormalDissipativeConstant";
NormalDissipativeConstant Builder<NormalDissipativeConstant>::build(const json& j)
{
	NormalDissipativeConstant x;
	x.set( j );
	return x;
}

// ========================================== TANGENTIAL DAMPING ==========================================
template<> const string NamedType<TangentialDamping>::name = "TangentialDamping";
TangentialDamping Builder<TangentialDamping>::build(const json& j)
{
	TangentialDamping x;
	x.set( j );
	return x;
}

// ========================================== FRICTION PARAMETER ==========================================
template<> const string NamedType<FrictionParameter>::name = "FrictionParameter";
FrictionParameter Builder<FrictionParameter>::build(const json& j)
{
	FrictionParameter x;
	x.set( j );
	return x;
}

// ========================================== TANGENTIAL KAPPA ==========================================
template<> const string NamedType<TangentialKappa>::name = "TangentialKappa";
TangentialKappa Builder<TangentialKappa>::build(const json& j)
{
	TangentialKappa x;
	x.set( j );
	return x;
}

// ========================================== ELECTRIC CHARGE ==========================================
template<> const string NamedType<ElectricCharge>::name = "ElectricCharge";
ElectricCharge Builder<ElectricCharge>::build(const json& j)
{
	ElectricCharge x;
	x.set( j );
	return x;
}

} // psin