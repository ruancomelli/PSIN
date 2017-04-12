#ifndef PROPERTY_LIST_H
#define PROPERTY_LIST_H

// PropertyLib
#include <Property.hpp>

namespace PropertyDefinitions{

	// Assigns value to destination if value is positive
	void setPositive( const double & value, double & destination);

	struct Mass : public Property<double>
	{
		Mass();

		static const std::string name;
	};


	struct Volume : public Property<double>
	{
		Volume();

		static const std::string name;
	};
	
	struct MomentOfInertia : public Property<double>
	{
		MomentOfInertia();

		static const std::string name;
	};
	
	struct ElasticModulus : public Property<double>
	{
		ElasticModulus();

		static const std::string name;
	};
	
	struct DissipativeConstant : public Property<double>
	{
		DissipativeConstant();

		static const std::string name;
	};
	
	struct PoissonRatio : public Property<double>
	{
		PoissonRatio();

		static const std::string name;
	};
	
	struct NormalDissipativeConstant : public Property<double>
	{
		NormalDissipativeConstant();

		static const std::string name;
	};
	
	struct TangentialDamping : public Property<double>
	{
		TangentialDamping();

		static const std::string name;
	};
	
	struct FrictionParameter : public Property<double>
	{
		FrictionParameter();

		static const std::string name;
	};
	
	struct TangentialKappa : public Property<double>
	{
		TangentialKappa();

		static const std::string name;
	};
	
	struct ElectricCharge : public Property<double>
	{
		ElectricCharge();

		static const std::string name;
	};
};

#endif
