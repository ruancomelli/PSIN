#include <PropertyDefinitions.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <string.hpp>

// Standard
#include <iostream>

namespace psin {
	
// ========================================== MASS ==========================================
template<> const string NamedType<Mass>::name = "Mass";
Mass Builder<Mass>::build(json& j)
{
	Mass x;
	x.set( j[NamedType<Mass>::name] );
	return x;
}

// ========================================== VOLUME ==========================================
template<> const string NamedType<Volume>::name = "Volume";
Volume Builder<Volume>::build(json& j)
{
	Volume x;
	x.set( j[NamedType<Volume>::name] );
	return x;
}

// ========================================== MOMENT OF INERTIA ==========================================
template<> const string NamedType<MomentOfInertia>::name = "MomentOfInertia";
MomentOfInertia Builder<MomentOfInertia>::build(json& j)
{
	MomentOfInertia x;
	x.set( j[NamedType<MomentOfInertia>::name] );
	return x;
}

// ========================================== MOMENT OF INERTIA ==========================================
template<> const string NamedType<Radius>::name = "Radius";
Radius Builder<Radius>::build(json& j)
{
	Radius x;
	x.set( j[NamedType<Radius>::name] );
	return x;
}

// ========================================== ELASTIC MODULUS ==========================================
template<> const string NamedType<ElasticModulus>::name = "ElasticModulus";
ElasticModulus Builder<ElasticModulus>::build(json& j)
{
	ElasticModulus x;
	x.set( j[NamedType<ElasticModulus>::name] );
	return x;
}

// ========================================== DISSIPATIVE CONSTANT ==========================================
template<> const string NamedType<DissipativeConstant>::name = "DissipativeConstant";
DissipativeConstant Builder<DissipativeConstant>::build(json& j)
{
	DissipativeConstant x;
	x.set( j[NamedType<DissipativeConstant>::name] );
	return x;
}

// ========================================== POISSON RATIO ==========================================
template<> const string NamedType<PoissonRatio>::name = "PoissonRatio";
PoissonRatio Builder<PoissonRatio>::build(json& j)
{
	PoissonRatio x;
	x.set( j[NamedType<PoissonRatio>::name] );
	return x;
}

// ========================================== NORMAL DISSIPATIVE CONSTANT ==========================================
template<> const string NamedType<NormalDissipativeConstant>::name = "NormalDissipativeConstant";
NormalDissipativeConstant Builder<NormalDissipativeConstant>::build(json& j)
{
	NormalDissipativeConstant x;
	x.set( j[NamedType<NormalDissipativeConstant>::name] );
	return x;
}

// ========================================== TANGENTIAL DAMPING ==========================================
template<> const string NamedType<TangentialDamping>::name = "TangentialDamping";
TangentialDamping Builder<TangentialDamping>::build(json& j)
{
	TangentialDamping x;
	x.set( j[NamedType<TangentialDamping>::name] );
	return x;
}

// ========================================== FRICTION PARAMETER ==========================================
template<> const string NamedType<FrictionParameter>::name = "FrictionParameter";
FrictionParameter Builder<FrictionParameter>::build(json& j)
{
	FrictionParameter x;
	x.set( j[NamedType<FrictionParameter>::name] );
	return x;
}

// ========================================== TANGENTIAL KAPPA ==========================================
template<> const string NamedType<TangentialKappa>::name = "TangentialKappa";
TangentialKappa Builder<TangentialKappa>::build(json& j)
{
	TangentialKappa x;
	x.set( j[NamedType<TangentialKappa>::name] );
	return x;
}

// ========================================== ELECTRIC CHARGE ==========================================
template<> const string NamedType<ElectricCharge>::name = "ElectricCharge";
ElectricCharge Builder<ElectricCharge>::build(json& j)
{
	ElectricCharge x;
	x.set( j[NamedType<ElectricCharge>::name] );
	return x;
}

} // psin