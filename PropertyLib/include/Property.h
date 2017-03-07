#ifndef RAW_PROPERTY_H
#define RAW_PROPERTY_H

// UtilsLib
#include <SharedPointer.h>
#include <Any.h>

// Standard
#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;


template<typename...> class Property;

template<typename type>
void defaultSetter(const type & value, type & destination);

template<typename type>
type defaultGetter(const type & value);

template<typename type>
bool defaultInputMethod(ifstream & in, Any & value);

template<typename type>
bool defaultOutputMethod(ofstream & out, Any & value);



template<typename interfaceType, typename storedType>
class Property<interfaceType, storedType>
{

	template<typename interfaceType, typename storedType>
	using PropertyPtr = SharedPointer< Property<interfaceType, storedType> >;

	public:
		typedef bool (*inputMethodType)(ifstream & in, Any & value);
		typedef bool (*outputMethodType)(ofstream & in, Any & value);

		// Constructors
		Property();
		explicit Property(const string & name);
		Property(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &));

		// Set and get name
		void setName(const string & name);
		string getName(void) const;

		// Set setter and getter
		void setSetterFunction( void (*setterFunction)(const interfaceType & value, storedType & destination) );
		void setGetterFunction( interfaceType (*getterFunction)(const storedType & value) );
		void setInputMethod( inputMethodType newInputMethod );
		void setOutputMethod( outputMethodType newOutputMethod );

		void (*setter)(const interfaceType & value, storedType & destination) = NULL;
		interfaceType (*getter)(const storedType &) = NULL;
		inputMethodType inputMethod = NULL;
		outputMethodType outputMethod = NULL;

	private:

		string name;

}; // class Property<interfaceType, storedType>

template<typename type>
class Property<type> : public Property<type, type>
{
	public:
		Property();
		explicit Property(const string & name, void (*setterFunction)(const type &, type &) = defaultSetter<type>, type (*getterFunction)(const type &) = defaultGetter<type>);
}; // class Property<type, type>

template<typename interfaceType, typename storedType>
using PropertyPtr = SharedPointer< Property<interfaceType, storedType> >;

#include <Property.tpp>

#endif
