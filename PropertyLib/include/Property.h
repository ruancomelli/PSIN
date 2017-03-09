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



template<typename InterfaceType, typename StoredType>
class Property<InterfaceType, StoredType>
{

	template<typename InterfaceType, typename StoredType>
	using PropertyPtr = SharedPointer< Property<InterfaceType, StoredType> >;

	public:
		typedef bool (*InputMethodType)(std::ifstream & in, Any & value);
		typedef bool (*OutputMethodType)(std::ofstream & in, Any & value);

		typedef void (*SetterType)(const InterfaceType & value, StoredType & destination);
		typedef InterfaceType (*GetterType)(const StoredType & value);

		// Constructors
		Property();
		explicit Property(const string & name);
		Property(const string & name, SetterType setterFunction, GetterType getterFunction);

		// Set and get name
		void setName(const string & name);
		string getName(void) const;

		// Set setter and getter
		void setSetterFunction( SetterType setterFunction );
		void setGetterFunction( GetterType getterFunction );
		void setInputMethod( InputMethodType newInputMethod );
		void setOutputMethod( OutputMethodType newOutputMethod );

		SetterType setter = NULL;
		GetterType getter = NULL;
		InputMethodType inputMethod = NULL;
		OutputMethodType outputMethod = NULL;

	private:

		string name;

}; // class Property<InterfaceType, StoredType>

template<typename type>
class Property<type> : public Property<type, type>
{
	public:
		typedef void (*SetterType)(const type & value, type & destination);
		typedef type (*GetterType)(const type & value);

		// Constructors
		Property();
		explicit Property(const string & name, SetterType setterFunction = defaultSetter<type>, GetterType getterFunction = defaultGetter<type>);
}; // class Property<type, type>

template<typename InterfaceType, typename StoredType>
using PropertyPtr = SharedPointer< Property<InterfaceType, StoredType> >;

#include <Property.tpp>

#endif
