#ifndef PROPERTY_DEFINITIONS_HPP
#define PROPERTY_DEFINITIONS_HPP

#include <PropertyDefinitions/Color.hpp>
#include <PropertyDefinitions/Gravity.hpp>

// PropertyLib
#include <PositiveProperty.hpp>
#include <Property.hpp>

// JSONLib
#include <json.hpp>

namespace psin {

struct Mass : public PositiveProperty<double>
{
	Mass();
	Mass(const double & value);
};
void from_json(const json& j, Mass &);
void to_json(json& j, const Mass &);

struct Volume : public PositiveProperty<double>
{
	Volume();
	Volume(const double & value);
};
void from_json(const json& j, Volume &);
void to_json(json& j, const Volume &);


struct MomentOfInertia : public PositiveProperty<double>
{
	MomentOfInertia();
	MomentOfInertia(const double & value);
};
void from_json(const json& j, MomentOfInertia &);
void to_json(json& j, const MomentOfInertia &);


struct Radius : public PositiveProperty<double>
{
	Radius();
	Radius(const double & value);
};
void from_json(const json& j, Radius &);
void to_json(json& j, const Radius &);


struct ElasticModulus : public PositiveProperty<double>
{
	ElasticModulus();
	ElasticModulus(const double & value);
};
void from_json(const json& j, ElasticModulus &);
void to_json(json& j, const ElasticModulus &);


struct DissipativeConstant : public Property<double>
{
	DissipativeConstant();
	DissipativeConstant(const double & value);
};
void from_json(const json& j, DissipativeConstant &);
void to_json(json& j, const DissipativeConstant &);


struct PoissonRatio : public Property<double>
{
	PoissonRatio();
	PoissonRatio(const double & value);
};
void from_json(const json& j, PoissonRatio &);
void to_json(json& j, const PoissonRatio &);


struct NormalDissipativeConstant : public PositiveProperty<double>
{
	NormalDissipativeConstant();
	NormalDissipativeConstant(const double & value);
};
void from_json(const json& j, NormalDissipativeConstant &);
void to_json(json& j, const NormalDissipativeConstant &);


struct TangentialDamping : public PositiveProperty<double>
{
	TangentialDamping();
	TangentialDamping(const double & value);
};
void from_json(const json& j, TangentialDamping &);
void to_json(json& j, const TangentialDamping &);


struct FrictionParameter : public PositiveProperty<double>
{
	FrictionParameter();
	FrictionParameter(const double & value);
};
void from_json(const json& j, FrictionParameter &);
void to_json(json& j, const FrictionParameter &);


struct TangentialKappa : public PositiveProperty<double>
{
	TangentialKappa();
	TangentialKappa(const double & value);
};
void from_json(const json& j, TangentialKappa &);
void to_json(json& j, const TangentialKappa &);


struct ElectricCharge : public Property<double>
{
	ElectricCharge();
	ElectricCharge(const double & value);
};
void from_json(const json& j, ElectricCharge &);
void to_json(json& j, const ElectricCharge &);
	
} // psin

#endif // PROPERTY_DEFINITIONS_HPP
