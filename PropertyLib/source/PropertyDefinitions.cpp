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
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== VOLUME ==========================================
template<> const string NamedType<Volume>::name = "Volume";
void from_json(const json& j, Volume x &)
{
	x = Volume(j);
}
void to_json(json& j, const Volume x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== MOMENT OF INERTIA ==========================================
template<> const string NamedType<MomentOfInertia>::name = "MomentOfInertia";
void from_json(const json& j, MomentOfInertia x &)
{
	x = MomentOfInertia(j);
}
void to_json(json& j, const MomentOfInertia x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== MOMENT OF INERTIA ==========================================
template<> const string NamedType<Radius>::name = "Radius";
void from_json(const json& j, Radius x &)
{
	x = Radius(j);
}
void to_json(json& j, const Radius x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== ELASTIC MODULUS ==========================================
template<> const string NamedType<ElasticModulus>::name = "ElasticModulus";
void from_json(const json& j, ElasticModulus x &)
{
	x = ElasticModulus(j);
}
void to_json(json& j, const ElasticModulus x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== DISSIPATIVE CONSTANT ==========================================
template<> const string NamedType<DissipativeConstant>::name = "DissipativeConstant";
void from_json(const json& j, DissipativeConstant x &)
{
	x = DissipativeConstant(j);
}
void to_json(json& j, const DissipativeConstant x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== POISSON RATIO ==========================================
template<> const string NamedType<PoissonRatio>::name = "PoissonRatio";
void from_json(const json& j, PoissonRatio x &)
{
	x = PoissonRatio(j);
}
void to_json(json& j, const PoissonRatio x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== NORMAL DISSIPATIVE CONSTANT ==========================================
template<> const string NamedType<NormalDissipativeConstant>::name = "NormalDissipativeConstant";
void from_json(const json& j, NormalDissipativeConstant x &)
{
	x = NormalDissipativeConstant(j);
}
void to_json(json& j, const NormalDissipativeConstant x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== TANGENTIAL DAMPING ==========================================
template<> const string NamedType<TangentialDamping>::name = "TangentialDamping";
void from_json(const json& j, TangentialDamping x &)
{
	x = TangentialDamping(j);
}
void to_json(json& j, const TangentialDamping x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== FRICTION PARAMETER ==========================================
template<> const string NamedType<FrictionParameter>::name = "FrictionParameter";
void from_json(const json& j, FrictionParameter x &)
{
	x = FrictionParameter(j);
}
void to_json(json& j, const FrictionParameter x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== TANGENTIAL KAPPA ==========================================
template<> const string NamedType<TangentialKappa>::name = "TangentialKappa";
void from_json(const json& j, TangentialKappa x &)
{
	x = TangentialKappa(j);
}
void to_json(json& j, const TangentialKappa x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

// ========================================== ELECTRIC CHARGE ==========================================
template<> const string NamedType<ElectricCharge>::name = "ElectricCharge";
void from_json(const json& j, ElectricCharge x &)
{
	x = ElectricCharge(j);
}
void to_json(json& j, const ElectricCharge x &)
{
	if(x.assigned()) j = x.get();
	else j = null;
}

} // psin