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

template<typename type>
bool defaultInputMethod(std::ifstream & in, Any & value)
{
	type newValue;

	in >> newValue;
	value = newValue;

	return true;
}

template<typename type>
bool defaultOutputMethod(std::ofstream & out, Any & value)
{
	out << anyCast<type>(value);

	return true;
}



// Constructors

template<typename InterfaceType, typename storedType>
Property<InterfaceType, storedType>::Property()
	: name("Nameless")
{
	this->inputMethod = defaultInputMethod<InterfaceType>;
	this->outputMethod = defaultOutputMethod<InterfaceType>;
}

template<typename InterfaceType, typename storedType>
Property<InterfaceType, storedType>::Property(const string & name)
{
	this->setName(name);

	this->inputMethod = defaultInputMethod<InterfaceType>;
	this->outputMethod = defaultOutputMethod<InterfaceType>;
}

template<typename InterfaceType, typename storedType>
Property<InterfaceType, storedType>::Property(const string & name, setterType setterFunction, getterType getterFunction)
{
	this->name = name;

	this->setter = setterFunction;
	this->getter = getterFunction;

	this->inputMethod = defaultInputMethod<InterfaceType>;
	this->outputMethod = defaultOutputMethod<InterfaceType>;
}


// Set and get name

template<typename InterfaceType, typename storedType>
void Property<InterfaceType, storedType>::setName(const string & name)
{
	if(!name.empty()) this->name = name;
	else this->name = "Nameless";
}

template<typename InterfaceType, typename storedType>
string Property<InterfaceType, storedType>::getName(void) const
{
	return this->name;
}


// Set setter and getter
template<typename InterfaceType, typename storedType>
void Property<InterfaceType, storedType>::setSetterFunction( setterType setterFunction )
{
	this->setter = setterFunction;
}

template<typename InterfaceType, typename storedType>
void Property<InterfaceType, storedType>::setGetterFunction( getterType getterFunction )
{
	this->getter = getterFunction;
}

// Set inputMethod and outputMethod
template<typename InterfaceType, typename storedType>
void Property<InterfaceType, storedType>::setInputMethod( inputMethodType newInputMethod )
{
	this->inputMethod = newInputMethod;
}

template<typename InterfaceType, typename storedType>
void Property<InterfaceType, storedType>::setOutputMethod( outputMethodType newOutputMethod )
{
	this->outputMethod = newOutputMethod;
}


// Only one type

// Constructors
// If types are equal, we are allowed to use defaultSetter and defaultGetter (copy setter and getters)
template<typename type>
Property<type>::Property()
	: Property<type, type>()
{
	setter = defaultSetter;
	getter = defaultGetter;
}

// If types are equal, we are allowed to use defaultSetter and defaultGetter (copy setter and getters)
template<typename type>
Property<type>::Property(const string & name, setterType setterFunction, getterType getterFunction)
	: Property<type, type>(name, setterFunction, getterFunction)
{
}
