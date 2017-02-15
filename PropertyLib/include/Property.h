#ifndef PROPERTY_H
#define PROPERTY_H

#include <RawProperty.h>
#include <string>

using namespace std;

template<typename...> class Property;	// Allows multiple template arguments

template<typename interfaceType, typename storedType>
class Property<interfaceType, storedType>
{
	public:
		// Constructors
		Property();
		explicit Property(string name);
		Property(const string & name, void (*setterFunction)(const interfaceType &, storedType &), interfaceType (*getterFunction)(const storedType &));
		explicit Property(const RawProperty<interfaceType, storedType> & rawProperty);
		Property(const RawProperty<interfaceType, storedType> & rawProperty, const interfaceType & value);

		// Setter and getter functions
		void set(const interfaceType & value);
		interfaceType get(void) const;

		// Set and get name
		void setName(const string & name);
		string getName(void) const;

		// Set RawProperty
		virtual void setRawProperty( const RawProperty<interfaceType, storedType> & raw );

	protected:
		RawProperty<interfaceType, storedType> rawProperty;
		storedType value;

}; // class Property

template<typename type>
class Property<type> : public Property<type, type>
{
	public:
		Property();
		explicit Property(const string & name, void (*setterFunction)(const type &, type &) = defaultSetter<type>, type (*getterFunction)(const type &) = defaultGetter<type>);
		explicit Property(const RawProperty<type, type> & rawProperty);
		Property(const RawProperty<type, type> & rawProperty, const type & value);
		explicit Property(const RawProperty<type> & rawProperty);
		Property(const RawProperty<type> & rawProperty, const type & value);

		// Set RawProperty
		virtual void setRawProperty( const RawProperty<type> & raw );
};

#include <Property.tpp>

#endif

