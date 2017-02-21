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
bool defaultInputMethod(ifstream & in, boost::any & value)
{
	type newValue;

	in >> newValue;
	value = newValue;

	return true;
}

template<typename type>
bool defaultOutputMethod(ofstream & out, boost::any & value)
{
	out << boost::any_cast<type>(value);

	return true;
}



// Constructors

template<typename interfaceType, typename storedType>
RawProperty<interfaceType, storedType>::RawProperty()
	: name("Nameless")
{
	this->inputMethod = defaultInputMethod<interfaceType>;
	this->outputMethod = defaultOutputMethod<interfaceType>;
}

template<typename interfaceType, typename storedType>
RawProperty<interfaceType, storedType>::RawProperty(const string & name)
{
	this->setName(name);

	this->inputMethod = defaultInputMethod<interfaceType>;
	this->outputMethod = defaultOutputMethod<interfaceType>;
}

template<typename interfaceType, typename storedType>
RawProperty<interfaceType, storedType>::RawProperty(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &))
{
	this->name = name;

	this->setter = setterFunction;
	this->getter = getterFunction;

	this->inputMethod = defaultInputMethod<interfaceType>;
	this->outputMethod = defaultOutputMethod<interfaceType>;
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

// Set inputMethod and outputMethod
template<typename interfaceType, typename storedType>
void RawProperty<interfaceType, storedType>::setInputMethod( inputMethodType newInputMethod )
{
	this->inputMethod = newInputMethod;
}

template<typename interfaceType, typename storedType>
void RawProperty<interfaceType, storedType>::setOutputMethod( outputMethodType newOutputMethod )
{
	this->outputMethod = newOutputMethod;
}

// Comparing
template<typename interfaceType, typename storedType>
bool RawProperty<interfaceType, storedType>::isSimilarTo( const RawProperty<interfaceType, storedType> & other ) const
{
	return ( this->getName() == other.getName() );
}

template<typename interfaceType, typename storedType>
bool RawProperty<interfaceType, storedType>::isSimilarTo( const RawPropertyPtr<interfaceType, storedType> & other ) const
{
	return ( this->getName() == other->getName() );
}

template<typename interfaceType, typename storedType>
bool RawProperty<interfaceType, storedType>::isEqualTo( const RawProperty<interfaceType, storedType> & other ) const
{
	bool test1 = ( this->getName() == other.getName() );
	bool test2 = ( this->setter == other.setter );
	bool test3 = ( this->getter == other.getter );

	return test1 && test2 && test3;
}

template<typename interfaceType, typename storedType>
bool RawProperty<interfaceType, storedType>::isEqualTo( const RawPropertyPtr<interfaceType, storedType> & other ) const
{
	bool test1 = ( this->getName() == other->getName() );
	bool test2 = ( this->setter == other->setter );
	bool test3 = ( this->getter == other->getter );

	return test1 && test2 && test3;
}


// Only one type

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
RawProperty<type>::RawProperty(const string & name, void (*setterFunction)(const type &, type &), type (*getterFunction)(const type &))
	: RawProperty<type, type>(name, setterFunction, getterFunction)
{
}
