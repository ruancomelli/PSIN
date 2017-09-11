#ifndef PROPERTY_DEFINITIONS_HPP
#define PROPERTY_DEFINITIONS_HPP

// PropertyLib
#include <PositiveProperty.hpp>
#include <Property.hpp>

// UtilsLib
#include <Builder.hpp>

// JSONLib
#include <json.hpp>

namespace psin {

struct Mass : public PositiveProperty<double>
{};
template<> struct Builder<Mass>
{
	static Mass build(json& j);
};

struct Volume : public PositiveProperty<double>
{};
template<> struct Builder<Volume>
{
	static Volume build(json& j);
};


struct MomentOfInertia : public PositiveProperty<double>
{};
template<> struct Builder<MomentOfInertia>
{
	static MomentOfInertia build(json& j);
};


struct Radius : public PositiveProperty<double>
{};
template<> struct Builder<Radius>
{
	static Radius build(json& j);
};


struct ElasticModulus : public PositiveProperty<double>
{};
template<> struct Builder<ElasticModulus>
{
	static ElasticModulus build(json& j);
};


struct DissipativeConstant : public Property<double>
{};
template<> struct Builder<DissipativeConstant>
{
	static DissipativeConstant build(json& j);
};


struct PoissonRatio : public Property<double>
{};
template<> struct Builder<PoissonRatio>
{
	static PoissonRatio build(json& j);
};


struct NormalDissipativeConstant : public PositiveProperty<double>
{};
template<> struct Builder<NormalDissipativeConstant>
{
	static NormalDissipativeConstant build(json& j);
};


struct TangentialDamping : public PositiveProperty<double>
{};
template<> struct Builder<TangentialDamping>
{
	static TangentialDamping build(json& j);
};


struct FrictionParameter : public PositiveProperty<double>
{};
template<> struct Builder<FrictionParameter>
{
	static FrictionParameter build(json& j);
};


struct TangentialKappa : public PositiveProperty<double>
{};
template<> struct Builder<TangentialKappa>
{
	static TangentialKappa build(json& j);
};


struct ElectricCharge : public Property<double>
{};
template<> struct Builder<ElectricCharge>
{
	static ElectricCharge build(json& j);
};
	
} // psin

#endif // PROPERTY_DEFINITIONS_HPP
