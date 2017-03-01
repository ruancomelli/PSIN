
template<typename interfaceType, typename storedType>
void ForceModel::requireProperty( const RawProperty<interfaceType, storedType> & property )
{
	this->requiredProperties.addProperty( property );
}