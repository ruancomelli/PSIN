// Constructors
template<typename interfaceType, typename storedType>
Property<interfaceType, storedType>::Property()
{}

template<typename interfaceType, typename storedType>
Property<interfaceType, storedType>::Property(string name)
	: rawProperty(name)
{}

template<typename interfaceType, typename storedType>
Property<interfaceType, storedType>::Property(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &))
	: rawProperty(name, setterFunction, getterFunction)
{}

template<typename interfaceType, typename storedType>
Property<interfaceType, storedType>::Property( const RawProperty<interfaceType, storedType> & rawProperty)
	: rawProperty(rawProperty)
{}

template<typename interfaceType, typename storedType>
Property<interfaceType, storedType>::Property( const RawProperty<interfaceType, storedType> & rawProperty, const interfaceType & value)
	: rawProperty(rawProperty)
{
	set(value);
}

// Setter and getter functions
template<typename interfaceType, typename storedType>
void Property<interfaceType, storedType>::set(const interfaceType & value)
{
	rawProperty.setter(value, this->value);
}

template<typename interfaceType, typename storedType>
interfaceType Property<interfaceType, storedType>::get(void) const
{
	return rawProperty.getter(this->value);
}