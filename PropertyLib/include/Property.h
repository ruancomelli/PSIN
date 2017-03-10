#ifndef RAW_PROPERTY_H
#define RAW_PROPERTY_H

// UtilsLib
#include <SharedPointer.h>
#include <Any.h>

// Standard
#include <fstream>
#include <functional>
#include <string>

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
	using PropertyPtr = SharedPointer< Property<InterfaceType, StoredType> >;

	public:
		using InputMethodType = std::function< bool(std::ifstream & in, Any & value) >;
		using OutputMethodType = std::function< bool(std::ofstream & in, Any & value) >;

		using SetterType = std::function< void(const InterfaceType & value, StoredType & destination) >;
		using GetterType = std::function< InterfaceType(const StoredType & value) >;

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

		SetterType setter;
		GetterType getter;
		InputMethodType inputMethod;
		OutputMethodType outputMethod;

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
}; // class Property<type>

template<typename ... Args>
using PropertyPtr = SharedPointer< Property<Args...> >;

#include <Property.tpp>

#endif
