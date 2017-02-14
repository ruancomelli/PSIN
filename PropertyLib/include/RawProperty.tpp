template<typename type>
void defaultSetter(const type & value, type & destination)
{
	destination = value;
}

template<typename type>
type defaultGetter(const type & value)
{
	return value;
}


// Constructors

template<typename interfaceType, typename storedType>
RawProperty<interfaceType, storedType>::RawProperty()
	: name("Nameless")
{
}

template<typename interfaceType, typename storedType>
RawProperty<interfaceType, storedType>::RawProperty(const string & name)
{
	this->setName(name);
}

template<typename interfaceType, typename storedType>
RawProperty<interfaceType, storedType>::RawProperty(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &))
{
	this->name = name;
	this->setter = setterFunction;
	this->getter = getterFunction;
}


// Set and get name

template<typename interfaceType, typename storedType>
void RawProperty<interfaceType, storedType>::setName(const string & name)
{
	if(!name.empty()) this->name = name;
	else this->name = "Nameless";
}

template<typename interfaceType, typename storedType>
string RawProperty<interfaceType, storedType>::getName(void) const
{
	return this->name;
}


// Set setter and getter
template<typename interfaceType, typename storedType>
void RawProperty<interfaceType, storedType>::setSetterFunction( void (*setterFunction)(const interfaceType & value, storedType & destination) )
{
	this->setter = setterFunction;
}

template<typename interfaceType, typename storedType>
void RawProperty<interfaceType, storedType>::setGetterFunction( interfaceType (*getterFunction)(const storedType & value) )
{
	this->getter = getterFunction;
}


// Constructors
// If types are equal, we are allowed to use defaultSetter and defaultGetter (copy setter and getters)
template<typename type>
RawProperty<type>::RawProperty()
	: RawProperty<type, type>()
{
	setter = defaultSetter;
	getter = defaultGetter;
}

// If types are equal, we are allowed to use defaultSetter and defaultGetter (copy setter and getters)
template<typename type>
RawProperty<type>::RawProperty(const string & name)
	: RawProperty<type, type>(name)
{
	setter = defaultSetter;
	getter = defaultGetter;
}

template<typename type>
RawProperty<type>::RawProperty(const string & name, void (*setterFunction)(const type &, type &), type (*getterFunction)(const type &))
	: RawProperty<type, type>(name, setterFunction, getterFunction)
{
}
