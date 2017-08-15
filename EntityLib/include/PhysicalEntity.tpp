#ifndef PHYSICAL_ENTITY_TPP
#define PHYSICAL_ENTITY_TPP

// UtilsLib
#include <Metaprogramming/type_list.hpp>

// ----- Constructors -----
template<typename ... PropertyTypes>
PhysicalEntity<PropertyTypes...>::PhysicalEntity()
{}

template<typename ... PropertyTypes>
template<typename...Us>
PhysicalEntity<PropertyTypes...>::PhysicalEntity(const PhysicalEntity<Us...> & other)
	: propertyTuple(other.propertyTuple)
{}

// ----- Return property -----
template<typename ... PropertyTypes>
template<typename PropertyType>
PropertyType& PhysicalEntity<PropertyTypes...>::property()
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'PhysicalEntity<PropertyTypes...>::property' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple);
}

template<typename ... PropertyTypes>
template<typename PropertyType>
PropertyType PhysicalEntity<PropertyTypes...>::property() const
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'PhysicalEntity<PropertyTypes...>::property' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple);
}

// ----- Input and output property -----
template<typename ... PropertyTypes>
template<typename PropertyType, typename istream_type>
bool PhysicalEntity<PropertyTypes...>::input(istream_type & in)
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'PhysicalEntity<PropertyTypes...>::input' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple).input(in);
}

template<typename ... PropertyTypes>
template<typename PropertyType, typename ostream_type>
bool PhysicalEntity<PropertyTypes...>::output(ostream_type & out) const
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'PhysicalEntity<PropertyTypes...>::output' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple).output(out);
}

// ----- Set and get property -----
template<typename ... PropertyTypes>
template<typename PropertyType, typename ValueType>
void PhysicalEntity<PropertyTypes...>::set(const ValueType & value)
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, 
		"Template parameter for function 'PhysicalEntity<PropertyTypes...>::set' must be in template parameter list in the specialization of 'PhysicalEntity'");

	this->template property<PropertyType>().set(value);
}

template<typename ... PropertyTypes>
template<typename PropertyType>
typename PropertyType::ValueType PhysicalEntity<PropertyTypes...>::get() const
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, 
		"Template parameter for function 'PhysicalEntity<PropertyTypes...>::get' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return this->template property<PropertyType>().get();
}

// ----- Check whether a property was assigned -----
template<typename ... PropertyTypes>
template<typename PropertyType>
bool PhysicalEntity<PropertyTypes...>::assigned() const
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'assigned' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple).assigned();
}

#endif
