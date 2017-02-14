#ifndef RAW_PROPERTY_H
#define RAW_PROPERTY_H

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

template<typename...> class RawProperty;

template<typename interfaceType, typename storedType>
class RawProperty<interfaceType, storedType>
{
	public:
		// Constructors
		RawProperty();
		explicit RawProperty(const string & name);
		RawProperty(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &));

		// Set and get name
		void setName(const string & name);
		string getName(void) const;

		// Set setter and getter
		void setSetterFunction( void (*setterFunction)(const interfaceType & value, storedType & destination) );
		void setGetterFunction( interfaceType (*getterFunction)(const storedType & value) );

		void (*setter)(const interfaceType & value, storedType & destination) = NULL;
		interfaceType (*getter)(const storedType &) = NULL;

	private:
		string name;

}; // class RawProperty

template<typename type>
class RawProperty<type> : public RawProperty<type, type>
{};

#endif