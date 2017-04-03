#ifndef FORCE_MODEL_TPP
#define FORCE_MODEL_TPP

template<typename InterfaceType, typename StoredType>
void ForceModel<SphericalParticle, SphericalParticle>::requireProperty( const Property<InterfaceType, StoredType> & property )
{
	this->requiredProperties.addProperty( property );
}

#endif
