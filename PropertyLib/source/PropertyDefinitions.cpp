#include <PropertyDefinitions.hpp>

// UtilsLib
#include <NamedType.hpp>
#include <string.hpp>

// Standard
#include <iostream>

namespace psin {
	
// ========================================== Mass ==========================================
Mass::Mass()
	: PositiveProperty<double>()
{}

Mass::Mass(const double & value)
	: PositiveProperty<double>(value)
{}

template<> const string NamedType<Mass>::name = "Mass";
void from_json(const json& j, Mass & x)
{
	x = Mass(j.get<double>());
}
void to_json(json& j, const Mass & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== Volume ==========================================
Volume::Volume()
	: PositiveProperty<double>()
{}

Volume::Volume(const double & value)
	: PositiveProperty<double>(value)
{}

template<> const string NamedType<Volume>::name = "Volume";
void from_json(const json& j, Volume & x)
{
	x = Volume(j.get<double>());
}
void to_json(json& j, const Volume & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== MomentOfInertia ==========================================
MomentOfInertia::MomentOfInertia()
	: PositiveProperty<double>()
{}

MomentOfInertia::MomentOfInertia(const double & value)
	: PositiveProperty<double>(value)
{}

template<> const string NamedType<MomentOfInertia>::name = "MomentOfInertia";
void from_json(const json& j, MomentOfInertia & x)
{
	x = MomentOfInertia(j.get<double>());
}
void to_json(json& j, const MomentOfInertia & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== Radius ==========================================
Radius::Radius()
	: PositiveProperty<double>()
{}

Radius::Radius(const double & value)
	: PositiveProperty<double>(value)
{}

template<> const string NamedType<Radius>::name = "Radius";
void from_json(const json& j, Radius & x)
{
	x = Radius(j.get<double>());
}
void to_json(json& j, const Radius & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== ElasticModulus ==========================================
ElasticModulus::ElasticModulus()
	: PositiveProperty<double>()
{}

ElasticModulus::ElasticModulus(const double & value)
	: PositiveProperty<double>(value)
{}

template<> const string NamedType<ElasticModulus>::name = "ElasticModulus";
void from_json(const json& j, ElasticModulus & x)
{
	x = ElasticModulus(j.get<double>());
}
void to_json(json& j, const ElasticModulus & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== DissipativeConstant ==========================================
DissipativeConstant::DissipativeConstant()
	: NonNegativeProperty<double>()
{}

DissipativeConstant::DissipativeConstant(const double & value)
	: NonNegativeProperty<double>(value)
{}

template<> const string NamedType<DissipativeConstant>::name = "DissipativeConstant";
void from_json(const json& j, DissipativeConstant & x)
{
	x = DissipativeConstant(j.get<double>());
}
void to_json(json& j, const DissipativeConstant & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== PoissonRatio ==========================================
PoissonRatio::PoissonRatio()
	: Property<double>()
{}

PoissonRatio::PoissonRatio(const double & value)
	: Property<double>(value)
{}

template<> const string NamedType<PoissonRatio>::name = "PoissonRatio";
void from_json(const json& j, PoissonRatio & x)
{
	x = PoissonRatio(j.get<double>());
}
void to_json(json& j, const PoissonRatio & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== NormalDissipativeConstant ==========================================
NormalDissipativeConstant::NormalDissipativeConstant()
	: NonNegativeProperty<double>()
{}

NormalDissipativeConstant::NormalDissipativeConstant(const double & value)
	: NonNegativeProperty<double>(value)
{}

template<> const string NamedType<NormalDissipativeConstant>::name = "NormalDissipativeConstant";
void from_json(const json& j, NormalDissipativeConstant & x)
{
	x = NormalDissipativeConstant(j.get<double>());
}
void to_json(json& j, const NormalDissipativeConstant & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== TangentialDamping ==========================================
TangentialDamping::TangentialDamping()
	: PositiveProperty<double>()
{}

TangentialDamping::TangentialDamping(const double & value)
	: PositiveProperty<double>(value)
{}

template<> const string NamedType<TangentialDamping>::name = "TangentialDamping";
void from_json(const json& j, TangentialDamping & x)
{
	x = TangentialDamping(j.get<double>());
}
void to_json(json& j, const TangentialDamping & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== FrictionParameter ==========================================
FrictionParameter::FrictionParameter()
	: PositiveProperty<double>()
{}

FrictionParameter::FrictionParameter(const double & value)
	: PositiveProperty<double>(value)
{}

template<> const string NamedType<FrictionParameter>::name = "FrictionParameter";
void from_json(const json& j, FrictionParameter & x)
{
	x = FrictionParameter(j.get<double>());
}
void to_json(json& j, const FrictionParameter & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== TangentialKappa ==========================================
TangentialKappa::TangentialKappa()
	: PositiveProperty<double>()
{}

TangentialKappa::TangentialKappa(const double & value)
	: PositiveProperty<double>(value)
{}

template<> const string NamedType<TangentialKappa>::name = "TangentialKappa";
void from_json(const json& j, TangentialKappa & x)
{
	x = TangentialKappa(j.get<double>());
}
void to_json(json& j, const TangentialKappa & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

// ========================================== ElectricCharge ==========================================
ElectricCharge::ElectricCharge()
	: Property<double>()
{}

ElectricCharge::ElectricCharge(const double & value)
	: Property<double>(value)
{}

template<> const string NamedType<ElectricCharge>::name = "ElectricCharge";
void from_json(const json& j, ElectricCharge & x)
{
	x = ElectricCharge(j.get<double>());
}
void to_json(json& j, const ElectricCharge & x)
{
	if(x.assigned()) j = x.get();
	else j = nullptr;
}

} // psin