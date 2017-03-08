#ifndef RAW_PROPERTY_H
#define RAW_PROPERTY_H

// UtilsLib
#include <SharedPointer.h>
#include <Any.h>

// Standard
#include <string>
#include <fstream>

using std::string;


template<typename...> class Property;

template<typename type>
void defaultSetter(const type & value, type & destination);

template<typename type>
type defaultGetter(const type & value);

template<typename type>
bool defaultInputMethod(std::ifstream & in, Any & value);

template<typename type>
bool defaultOutputMethod(std::ofstream & out, Any & value);



template<typename interfaceType, typename storedType>
class Property<interfaceType, storedType>
{

	template<typename interfaceType, typename storedType>
	using PropertyPtr = SharedPointer< Property<interfaceType, storedType> >;

	public:
		typedef bool (*inputMethodType)(std::ifstream & in, Any & value);
		typedef bool (*outputMethodType)(std::ofstream & in, Any & value);

		typedef void (*setterType)(const interfaceType & value, storedType & destination);
		typedef interfaceType (*getterType)(const storedType & value);

		// Constructors
		Property();
		explicit Property(const string & name);
		Property(const string & name, setterType setterFunction, getterType getterFunction);

		// Set and get name
		void setName(const string & name);
		string getName(void) const;

		// Set setter and getter
		void setSetterFunction( setterType setterFunction );
		void setGetterFunction( getterType getterFunction );
		void setInputMethod( inputMethodType newInputMethod );
		void setOutputMethod( outputMethodType newOutputMethod );

		setterType setter = NULL;
		getterType getter = NULL;
		inputMethodType inputMethod = NULL;
		outputMethodType outputMethod = NULL;

	private:

		string name;

}; // class Property<interfaceType, storedType>

template<typename type>
class Property<type> : public Property<type, type>
{
	public:
		typedef void (*setterType)(const type & value, type & destination);
		typedef type (*getterType)(const type & value);

		// Constructors
		Property();
		explicit Property(const string & name, setterType setterFunction = defaultSetter<type>, getterType getterFunction = defaultGetter<type>);
}; // class Property<type, type>

template<typename interfaceType, typename storedType>
using PropertyPtr = SharedPointer< Property<interfaceType, storedType> >;

#include <Property.tpp>

#endif
