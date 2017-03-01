
template<typename interfaceType, typename storedType>
void ForceModel::requireProperty( const Property<interfaceType, storedType> & property )
{
	this->requiredProperties.addProperty( property );
}