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
	static Mass build(const json& j);
};

struct Volume : public PositiveProperty<double>
{};
template<> struct Builder<Volume>
{
	static Volume build(const json& j);
};


struct MomentOfInertia : public PositiveProperty<double>
{};
template<> struct Builder<MomentOfInertia>
{
	static MomentOfInertia build(const json& j);
};


struct Radius : public PositiveProperty<double>
{};
template<> struct Builder<Radius>
{
	static Radius build(const json& j);
};


struct ElasticModulus : public PositiveProperty<double>
{};
template<> struct Builder<ElasticModulus>
{
	static ElasticModulus build(const json& j);
};


struct DissipativeConstant : public Property<double>
{};
template<> struct Builder<DissipativeConstant>
{
	static DissipativeConstant build(const json& j);
};


struct PoissonRatio : public Property<double>
{};
template<> struct Builder<PoissonRatio>
{
	static PoissonRatio build(const json& j);
};


struct NormalDissipativeConstant : public PositiveProperty<double>
{};
template<> struct Builder<NormalDissipativeConstant>
{
	static NormalDissipativeConstant build(const json& j);
};


struct TangentialDamping : public PositiveProperty<double>
{};
template<> struct Builder<TangentialDamping>
{
	static TangentialDamping build(const json& j);
};


struct FrictionParameter : public PositiveProperty<double>
{};
template<> struct Builder<FrictionParameter>
{
	static FrictionParameter build(const json& j);
};


struct TangentialKappa : public PositiveProperty<double>
{};
template<> struct Builder<TangentialKappa>
{
	static TangentialKappa build(const json& j);
};


struct ElectricCharge : public Property<double>
{};
template<> struct Builder<ElectricCharge>
{
	static ElectricCharge build(const json& j);
};
	
} // psin

#endif // PROPERTY_DEFINITIONS_HPP
