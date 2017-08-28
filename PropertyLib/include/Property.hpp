#ifndef PROPERTY_HPP
#define PROPERTY_HPP

// UtilsLib
#include <UniquePointer.hpp>

namespace psin {

template<typename T = double>
class Property
{
	public:
		Property<T>& operator=(const Property<T> & other);

		using ValueType = T;

		// Constructors
		Property();
		Property(const T & value);
		Property(const Property<T> & other);

		template<typename U>
		void set(const U & value);

		virtual T get() const;

		template<typename istream_type>
		bool input(istream_type & in);

		template<typename ostream_type>
		bool output(ostream_type & out) const;

		// Assigned
		bool assigned() const;

	protected:
		unique_ptr<T> value;

		void assign(const T & value);
		bool assignedFlag = false;
};

} // psin

#include <Property.tpp>

#endif // PROPERTY_HPP
