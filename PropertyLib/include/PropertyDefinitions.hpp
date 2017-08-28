#ifndef PROPERTY_DEFINITIONS_HPP
#define PROPERTY_DEFINITIONS_HPP

// Standard
#include <string>

// PropertyLib
#include <PositiveProperty.hpp>
#include <Property.hpp>

namespace psin {
namespace PropertyDefinitions{

	struct Mass : public PositiveProperty<double>
	{
		static const std::string name;
	};


	struct Volume : public PositiveProperty<double>
	{
		static const std::string name;
	};
	
	struct MomentOfInertia : public PositiveProperty<double>
	{
		static const std::string name;
	};

	struct Radius : public PositiveProperty<double>
	{
		static const std::string name;
	};
	
	struct ElasticModulus : public PositiveProperty<double>
	{
		static const std::string name;
	};
	
	struct DissipativeConstant : public Property<double>
	{
		static const std::string name;
	};
	
	struct PoissonRatio : public Property<double>
	{
		static const std::string name;
	};
	
	struct NormalDissipativeConstant : public PositiveProperty<double>
	{
		static const std::string name;
	};
	
	struct TangentialDamping : public PositiveProperty<double>
	{
		static const std::string name;
	};
	
	struct FrictionParameter : public PositiveProperty<double>
	{
		static const std::string name;
	};
	
	struct TangentialKappa : public PositiveProperty<double>
	{
		static const std::string name;
	};
	
	struct ElectricCharge : public Property<double>
	{
		static const std::string name;
	};
} // PropertyDefinitions
} // psin

#endif // PROPERTY_DEFINITIONS_HPP
