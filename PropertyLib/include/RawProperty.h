#ifndef RAW_PROPERTY_H
#define RAW_PROPERTY_H


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

template<typename...> class RawProperty;

template<typename interfaceType, typename storedType>
class RawProperty<interfaceType, storedType>
{
	public:
		// Constructors
		RawProperty();

		explicit RawProperty(const string & name);
		
		RawProperty(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &))
		{
			this->name = name;
			this->setter = setterFunction;
			this->getter = getterFunction;
		}

		// Set and get name
		void setName(const string & name)
		{
			if(!name.empty()) this->name = name;
			else this->name = "Nameless";
		}

		string getName(void) const
		{
			return this->name;
		}

		// Set setter and getter
		void setSetterFunction( void (*setterFunction)(const interfaceType & value, storedType & destination) )
		{
			this->setter = setterFunction;
		}
		void setGetterFunction( interfaceType (*getterFunction)(const storedType & value) )
		{
			this->getter = getterFunction;
		}

		void (*setter)(const interfaceType & value, storedType & destination) = NULL;
		interfaceType (*getter)(const storedType &) = NULL;

	private:
		string name;

}; // class RawProperty

template<typename type>
class RawProperty<type> : public RawProperty<type, type>
{};


template<typename type>


#endif
