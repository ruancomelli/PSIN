// ==============================================================================================================================
// ==============================================================================================================================
// PropertyList.h
// ==============================================================================================================================

Property<double> mass;
Property<double> volume;
Property<double> density;


// ----------------------------------------------------- begin NEW THINGS -----------------------------------------------------
double mass_from_v_and_rho(double v, double rho)
{
	return v * rho;
}

mass.depends(volume, density, mass_from_v_and_rho);
// ----------------------------------------------------- end NEW THINGS -----------------------------------------------------

// ==============================================================================================================================
// ==============================================================================================================================
// SphericalParticlePtrArrayKit.cpp
// ==============================================================================================================================
SphericalParticlePtrArrayKit::checkPropertyDependencies()
{
	for( auto& particle : *this )
	{
		particle.checkPropertyDependencies();
	}
}

// ==============================================================================================================================
// Somewhere after the input of particles
// ==============================================================================================================================
particleArray.checkPropertyDependencies();

// ==============================================================================================================================
// ==============================================================================================================================
// PhysicalEntity.cpp
// ==============================================================================================================================
PhysicalEntity::checkPropertyDependencies()
{
	this->propertyArray.checkDependencies();
}

// ==============================================================================================================================
// ==============================================================================================================================
// PropertyContainer.cpp
// ==============================================================================================================================
PropertyContainer::checkDependencies()
{
	// Suppose that mass depends on volume and density or on radius and density. Then
	// mass.dependencyListNames == { {"Volume", "Density"}, {"Radius", "Density"} }
	// Also, if dependency == dependencyList[0], density and radius are defined, but not volume, then
	// dependency = { {"Volume", "Density"}, {false, true} }
	// but if dependency == dependencyList[1], then
	// dependency = { {"Radius", "Density"}, {true, true} }

	for( property : propertyList )
	{
		for( dependency : property.dependencyList )
		{
			if( dependecy.isEverybodyTrue() )
			{
				property.calculateFromDependencies(); // I don't know how to do this
			}
		}
	}
}