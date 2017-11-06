#ifndef NON_NEGATIVE_PROPERTY_HPP
#define NON_NEGATIVE_PROPERTY_HPP

#include <Property.hpp>

namespace psin {
	
template<typename T>
class NonNegativeProperty : public Property<T>
{
	public:
		using ValueType = T;

		// Constructors
		NonNegativeProperty();
		NonNegativeProperty(const T & value);

		template<typename U>
		void set(const U & value);

};

} // psin

#include <NonNegativeProperty.tpp>

#endif
