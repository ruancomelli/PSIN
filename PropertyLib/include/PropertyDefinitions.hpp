#ifndef PROPERTY_LIST_H
#define PROPERTY_LIST_H

// Standard
#include <string>

// PropertyLib
#include <PositiveProperty.hpp>
#include <Property.hpp>

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
	
	struct ElectricCharge : public PositiveProperty<double>
	{
		static const std::string name;
	};
};

#endif
