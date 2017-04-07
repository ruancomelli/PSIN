#ifndef PROPERTY_LIST_H
#define PROPERTY_LIST_H

// PropertyLib
#include <Property.hpp>

// Standard
#include <string>

namespace PropertyDefinitions{

	// Assigns value to destination if value is positive
	void setPositive( const double & value, double & destination);

	class Mass : public Property<double>
	{
		Mass()
			: Named("Mass"),
		{
			this->setter = setPositive;
		}
	}

	class Volume : public Property<double>
	{
		Volume()
			: Named("Volume"),
		{
			this->setter = setPositive;
		}
	}
	
	class MomentOfInertia : public Property<double>
	{
		MomentOfInertia()
			: Named("MomentOfInertia"),
		{
			this->setter = setPositive;
		}
	}
	
	class ElasticModulus : public Property<double>
	{
		ElasticModulus()
			: Named("ElasticModulus"),
		{
			this->setter = setPositive;
		}
	}
	
	class DissipativeConstant : public Property<double>
	{
		DissipativeConstant()
			: Named("DissipativeConstant"),
		{}
	}
	
	class PoissonRatio : public Property<double>
	{
		PoissonRatio()
			: Named("PoissonRatio"),
		{}
	}
	
	class NormalDissipativeConstant : public Property<double>
	{
		NormalDissipativeConstant()
			: Named("NormalDissipativeConstant"),
		{
			this->setter = setPositive;
		}
	}
	
	class TangentialDamping : public Property<double>
	{
		TangentialDamping()
			: Named("TangentialDamping"),
		{
			this->setter = setPositive;
		}
	}
	
	class FrictionParameter : public Property<double>
	{
		FrictionParameter()
			: Named("FrictionParameter"),
		{
			this->setter = setPositive;
		}
	}
	
	class TangentialKappa : public Property<double>
	{
		TangentialKappa()
			: Named("TangentialKappa"),
		{
			this->setter = setPositive;
		}
	}
	
	class ElectricCharge : public Property<double>
	{
		ElectricCharge()
			: Named("ElectricCharge"),
		{
			this->setter = setPositive;
		}
	}
};

#endif
