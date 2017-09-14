#include <PropertyDefinitions.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <string.hpp>

// Standard
#include <iostream>

namespace psin {
	
// ========================================== MASS ==========================================
template<> const string NamedType<Mass>::name = "Mass";
void from_json(const json& j, Mass x &)
{
	x = Mass(j);
}
void to_json(json& j, const Mass x &)
{
	j = x.get();
}

// ========================================== VOLUME ==========================================
template<> const string NamedType<Volume>::name = "Volume";
void from_json(const json& j, Volume x &)
{
	x = Volume(j);
}
void to_json(json& j, const Volume x &)
{
	j = x.get();
}

// ========================================== MOMENT OF INERTIA ==========================================
template<> const string NamedType<MomentOfInertia>::name = "MomentOfInertia";
void from_json(const json& j, MomentOfInertia x &)
{
	x = MomentOfInertia(j);
}
void to_json(json& j, const MomentOfInertia x &)
{
	j = x.get();
}

// ========================================== MOMENT OF INERTIA ==========================================
template<> const string NamedType<Radius>::name = "Radius";
void from_json(const json& j, Radius x &)
{
	x = Radius(j);
}
void to_json(json& j, const Radius x &)
{
	j = x.get();
}

// ========================================== ELASTIC MODULUS ==========================================
template<> const string NamedType<ElasticModulus>::name = "ElasticModulus";
void from_json(const json& j, ElasticModulus x &)
{
	x = ElasticModulus(j);
}
void to_json(json& j, const ElasticModulus x &)
{
	j = x.get();
}

// ========================================== DISSIPATIVE CONSTANT ==========================================
template<> const string NamedType<DissipativeConstant>::name = "DissipativeConstant";
void from_json(const json& j, DissipativeConstant x &)
{
	x = DissipativeConstant(j);
}
void to_json(json& j, const DissipativeConstant x &)
{
	j = x.get();
}

// ========================================== POISSON RATIO ==========================================
template<> const string NamedType<PoissonRatio>::name = "PoissonRatio";
void from_json(const json& j, PoissonRatio x &)
{
	x = PoissonRatio(j);
}
void to_json(json& j, const PoissonRatio x &)
{
	j = x.get();
}

// ========================================== NORMAL DISSIPATIVE CONSTANT ==========================================
template<> const string NamedType<NormalDissipativeConstant>::name = "NormalDissipativeConstant";
void from_json(const json& j, NormalDissipativeConstant x &)
{
	x = NormalDissipativeConstant(j);
}
void to_json(json& j, const NormalDissipativeConstant x &)
{
	j = x.get();
}

// ========================================== TANGENTIAL DAMPING ==========================================
template<> const string NamedType<TangentialDamping>::name = "TangentialDamping";
void from_json(const json& j, TangentialDamping x &)
{
	x = TangentialDamping(j);
}
void to_json(json& j, const TangentialDamping x &)
{
	j = x.get();
}

// ========================================== FRICTION PARAMETER ==========================================
template<> const string NamedType<FrictionParameter>::name = "FrictionParameter";
void from_json(const json& j, FrictionParameter x &)
{
	x = FrictionParameter(j);
}
void to_json(json& j, const FrictionParameter x &)
{
	j = x.get();
}

// ========================================== TANGENTIAL KAPPA ==========================================
template<> const string NamedType<TangentialKappa>::name = "TangentialKappa";
void from_json(const json& j, TangentialKappa x &)
{
	x = TangentialKappa(j);
}
void to_json(json& j, const TangentialKappa x &)
{
	j = x.get();
}

// ========================================== ELECTRIC CHARGE ==========================================
template<> const string NamedType<ElectricCharge>::name = "ElectricCharge";
void from_json(const json& j, ElectricCharge x &)
{
	x = ElectricCharge(j);
}
void to_json(json& j, const ElectricCharge x &)
{
	j = x.get();
}

} // psin