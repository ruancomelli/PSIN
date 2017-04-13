#ifndef VALUED_PROPERTY_CONTAINER_H
#define VALUED_PROPERTY_CONTAINER_H

// PropertyLib
#include <PropertyContainer.hpp>

// Standard
#include <iostream>
#include <map>
#include <string>

// UtilsLib
#include <Any.hpp>


template<typename ... PropertyTypes>
class ValuedPropertyContainer : public PropertyContainer<PropertyTypes...>
{
	using string = std::string;

	public:

	private:

}; // class ValuedPropertyContainer



#include <ValuedPropertyContainer.tpp>

#endif // VALUED_PROPERTY_CONTAINER_H
