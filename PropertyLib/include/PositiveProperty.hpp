#ifndef POSITIVE_PROPERTY_HPP
#define POSITIVE_PROPERTY_HPP

#include <Property.hpp>

template<typename T>
class PositiveProperty : public Property<T>
{
	public:
		using ValueType = T;

		// Constructors
		PositiveProperty();
		PositiveProperty(const T & value);

		template<typename U>
		void set(const U & value);

};

#include <PositiveProperty.tpp>

#endif
