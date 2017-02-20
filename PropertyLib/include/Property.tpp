// Constructors
template<typename interfaceType, typename storedType>
Property<interfaceType, storedType>::Property()
	: rawProperty( new RawProperty<interfaceType, storedType>() )
{}

template<typename interfaceType, typename storedType>
Property<interfaceType, storedType>::Property(string name)
	: rawProperty( new RawProperty<interfaceType, storedType>(name) )
{}

template<typename interfaceType, typename storedType>
Property<interfaceType, storedType>::Property(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &))
	: rawProperty( new RawProperty<interfaceType, storedType>(name, setterFunction, getterFunction) )
{}

template<typename interfaceType, typename storedType>
Property<interfaceType, storedType>::Property( const RawProperty<interfaceType, storedType> & rawProperty)
	: rawProperty( new RawProperty<interfaceType, storedType>(rawProperty) )
{}

template<typename interfaceType, typename storedType>
Property<interfaceType, storedType>::Property( const RawProperty<interfaceType, storedType> & rawProperty, const interfaceType & value)
	: rawProperty( new RawProperty<interfaceType, storedType>(rawProperty) )
{
	set(value);
}

// Setter and getter functions
template<typename interfaceType, typename storedType>
void Property<interfaceType, storedType>::set(const interfaceType & value)
{
	rawProperty->setter(value, this->value);
}

template<typename interfaceType, typename storedType>
interfaceType Property<interfaceType, storedType>::get(void) const
{
	return rawProperty->getter(this->value);
}

// Get name
template<typename interfaceType, typename storedType>
string Property<interfaceType, storedType>::getName(void) const
{
	return this->rawProperty->getName();
}

// Set RawProperty
template<typename interfaceType, typename storedType>
void Property<interfaceType, storedType>::setRawProperty( const RawProperty<interfaceType, storedType> & raw )
{
	this->rawProperty = RawPropertyPtr<interfaceType, storedType>( new RawProperty<interfaceType, storedType>(raw));
}

template<typename interfaceType, typename storedType>
RawPropertyPtr<interfaceType, storedType> Property<interfaceType, storedType>::getRawProperty( void ) const
{
	return this->rawProperty;
}

// Property<type>

template<typename type>
Property<type>::Property() : Property<type, type>() 
{
	this->rawProperty->setSetterFunction( defaultSetter );
	this->rawProperty->setGetterFunction( defaultGetter );
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

// Set RawProperty
template<typename type>
void Property<type>::setRawProperty( const RawProperty<type> & raw )
{
	this->rawProperty = SharedPointer< RawProperty<type> >( new RawProperty<type>(raw));
}