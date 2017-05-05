#ifndef PROPERTY_HPP
#define PROPERTY_HPP

// Standard
#include <iostream>

// UtilsLib
#include <UniquePointer.hpp>

template<typename type = double>
class Property
{
	public:
		Property<type>& operator=(const Property<type> & other);

		using Type = type;

		// Constructors
		Property();
		Property(const type & value);
		Property(const Property<type> & other);

		virtual void set(const type & value);
		virtual type get() const;

		virtual bool input(std::istream & in);
		virtual bool output(std::ostream & out) const;

		// Assigned
		bool assigned() const;

	protected:
		UniquePointer<type> value;

		void assign(const type & value);
		bool assignedFlag = false;

};

#include <Property.tpp>

#endif
