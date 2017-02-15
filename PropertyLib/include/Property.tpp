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

// Set and Get name
template<typename interfaceType, typename storedType>
void Property<interfaceType, storedType>::setName(const string & name)
{
	this->rawProperty.setName(name);
}

template<typename interfaceType, typename storedType>
string Property<interfaceType, storedType>::getName(void) const
{
	return this->rawProperty.getName();
}

// Set RawProperty
template<typename interfaceType, typename storedType>
void Property<interfaceType, storedType>::setRawProperty( const RawProperty<interfaceType, storedType> & raw )
{
	this->rawProperty = raw;
}


// Property<type>

// Set RawProperty
template<typename type>
Property<type>::Property() : Property<type, type>() 
{
	this->rawProperty.setSetterFunction( defaultSetter );
	this->rawProperty.setGetterFunction( defaultGetter );
}

template<typename type>
Property<type>::Property(const string & name, void (*setterFunction)(const type &, type &), type (*getterFunction)(const type &))
	: Property<type, type>(name, setterFunction, getterFunction) 
{
}

template<typename type>
Property<type>::Property(const RawProperty<type, type> & rawProperty)
	: Property<type, type>(rawProperty) 
{
}

template<typename type>
Property<type>::Property(const RawProperty<type, type> & rawProperty, const type & value)
	: Property<type, type>(rawProperty, value) 
{
}

template<typename type>
Property<type>::Property(const RawProperty<type> & rawProperty)
	: Property<type, type>(rawProperty) 
{
}

template<typename type>
Property<type>::Property(const RawProperty<type> & rawProperty, const type & value)
	: Property<type, type>(rawProperty, value)
{
}

template<typename type>
void Property<type>::setRawProperty( const RawProperty<type> & raw )
{
	this->rawProperty = raw;
}