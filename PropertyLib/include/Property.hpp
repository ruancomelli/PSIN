#ifndef PROPERTY_HPP
#define PROPERTY_HPP

// Standard
#include <iostream>
#include <memory>

template<typename type>
class Property
{
	public:
		using Type = type;

		// Constructors
		Property();
		Property(const type & value);
		virtual void set(const type & value);
		virtual type get() const;

		virtual bool input(std::istream & in);
		virtual bool output(std::ostream & out) const;

		// Assigned
		bool assigned() const;

	protected:
		std::unique_ptr<type> value;

		void assign(const type & value);
		bool assignedFlag = false;

}; // class Property<type>

#include <Property.tpp>

#endif
