//newProperties_pseudo-test

#include <iostream>
#include <string>

using namespace std;

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

template<typename...> class RawPhysicalProperty;

template<typename interfaceType, typename storedType>
class RawPhysicalProperty<interfaceType, storedType>
{
	public:
		// Constructors
		RawPhysicalProperty()
			: name("Nameless")
		{
			if( std::is_same<interfaceType, storedType>::value )	// If both classes are equal, we can use default setter and getter functions
			{
				setter = defaultSetter;
				getter = defaultGetter;
			}
		}

		explicit RawPhysicalProperty(const string & name)
		{
			this->setName(name);

			if( std::is_same<interfaceType, storedType>::value )	// If both classes are equal, we can use default setter and getter functions
			{
				setter = defaultSetter;
				getter = defaultGetter;
			}
		}

		RawPhysicalProperty(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &))
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

}; // class RawPhysicalProperty

template<typename type>
class RawPhysicalProperty<type> : public RawPhysicalProperty<type, type>
{};

template<typename interfaceType, typename storedType>
using RawPhysicalPropertyPtr = SharedPointer< RawPhysicalProperty<interfaceType, storedType> >


template<typename...> class PhysicalProperty;	// Allows multiple template arguments

template<typename interfaceType, typename storedType>
class PhysicalProperty<interfaceType, storedType>
{
	public:
		// Constructors
		PhysicalProperty()
		{}

		explicit PhysicalProperty(string name)
			: rawProperty(name)
		{}

		PhysicalProperty(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &))
			: rawProperty(name, setterFunction, getterFunction)
		{}

		PhysicalProperty( const RawPhysicalProperty<interfaceType, storedType> & rawProperty)
			: rawProperty(rawProperty)
		{}

		PhysicalProperty( const RawPhysicalProperty<interfaceType, storedType> & rawProperty, const interfaceType & value)
			: rawProperty(rawProperty)
		{
			set(value);
		}

		// Setter and getter functions
		void set(const interfaceType & value)
		{
			rawProperty.setter(value, this->value);
		}

		interfaceType get(void)
		{
			return rawProperty.getter(this->value);
		}

	private:
		RawPhysicalProperty<interfaceType, storedType> rawProperty;
		storedType value;

}; // class PhysicalProperty

template<typename type>
class PhysicalProperty<type> : public PhysicalProperty<type, type>
{};

void setMass( const double & value, double & destination)
{
	if(value > 0) destination = value;
	else cout << "Error: Mass must be positive.";
}

int main(void)
{
	RawPhysicalProperty<double> mass;
	mass.setName("Mass");
	mass.setSetterFunction( setMass );




	PhysicalProperty<double, double> myParticleMass(mass, 10);
	PhysicalProperty<double, double> myOtherParticleMass(mass, 20);


	cout << "Name: " << mass.getName() << endl;
	cout << "Initial value: " << myParticleMass.get() << endl;
	cout << "Trying to set mass = 10" << endl;
	myParticleMass.set(10);
	cout << "Value after mass = 10 : " << myParticleMass.get() << endl;
	cout << "Trying to set mass = -3" << endl;
	myParticleMass.set(-3);
	cout << "Value after mass = -3 : " << myParticleMass.get() << endl;

}