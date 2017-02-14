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
		Property(const RawProperty<interfaceType, storedType> & rawProperty);
		Property(const RawProperty<interfaceType, storedType> & rawProperty, const interfaceType & value);

		// Setter and getter functions
		void set(const interfaceType & value);
		interfaceType get(void) const;

	private:
		RawProperty<interfaceType, storedType> rawProperty;
		storedType value;

}; // class Property

template<typename type>
class Property<type> : public Property<type, type>
{};

#include <Property.tpp>

#endif

