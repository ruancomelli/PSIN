#ifndef POSITIVE_PROPERTY_HPP
#define POSITIVE_PROPERTY_HPP

#include <Property.hpp>

template<typename type>
class PositiveProperty : public Property<type>
{
	public:
		using Type = type;

		// Constructors
		PositiveProperty();
		PositiveProperty(const type & value);

		virtual void set(const type & value);

}; // class Property<type>

#include <PositiveProperty.tpp>

#endif // POSITIVE_PROPERTY_HPP
