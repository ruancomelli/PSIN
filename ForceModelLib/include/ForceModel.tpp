#ifndef FORCE_MODEL_TPP
#define FORCE_MODEL_TPP

template<typename InterfaceType, typename storedType>
void ForceModel::requireProperty( const Property<InterfaceType, storedType> & property )
{
	this->requiredProperties.addProperty( property );
}

#endif