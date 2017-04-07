#ifndef PROPERTY_LIST_H
#define PROPERTY_LIST_H

// PropertyLib
#include <Property.hpp>

// Standard
#include <string>

namespace PropertyDefinitions{

	// Assigns value to destination if value is positive
	void setPositive( const double & value, double & destination);

	struct Mass : public Property<double>
	{
		Mass();
	};

	struct Volume : public Property<double>
	{
		Volume();
	};
	
	struct MomentOfInertia : public Property<double>
	{
		MomentOfInertia();
	};
	
	struct ElasticModulus : public Property<double>
	{
		ElasticModulus();
	};
	
	struct DissipativeConstant : public Property<double>
	{
		DissipativeConstant();
	};
	
	struct PoissonRatio : public Property<double>
	{
		PoissonRatio();
	};
	
	struct NormalDissipativeConstant : public Property<double>
	{
		NormalDissipativeConstant();
	};
	
	struct TangentialDamping : public Property<double>
	{
		TangentialDamping();
	};
	
	struct FrictionParameter : public Property<double>
	{
		FrictionParameter();
	};
	
	struct TangentialKappa : public Property<double>
	{
		TangentialKappa();
	};
	
	struct ElectricCharge : public Property<double>
	{
		ElectricCharge();
	};
};

#endif
