#ifndef PHYSICAL_ENTITY_TPP
#define PHYSICAL_ENTITY_TPP

// UtilsLib
#include <Metaprogramming/type_list.hpp>

// ----- Constructors -----
template<typename ... PropertyTypes>
PhysicalEntityModel<PropertyTypes...>::PhysicalEntityModel()
{}

template<typename ... PropertyTypes>
PhysicalEntityModel<PropertyTypes...>::PhysicalEntityModel(const PhysicalEntityModel<PropertyTypes...> & other)
	: propertyTuple(other.propertyTuple)
{}

// ----- Return property -----
template<typename ... PropertyTypes>
template<typename PropertyType>
PropertyType& PhysicalEntityModel<PropertyTypes...>::property()
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'PhysicalEntityModel<PropertyTypes...>::property' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple);
}

template<typename ... PropertyTypes>
template<typename PropertyType>
PropertyType PhysicalEntityModel<PropertyTypes...>::property() const
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'PhysicalEntityModel<PropertyTypes...>::property' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple);
}

// ----- Input and output property -----
template<typename ... PropertyTypes>
template<typename PropertyType, typename istream_type>
bool PhysicalEntityModel<PropertyTypes...>::input(istream_type & in)
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'PhysicalEntityModel<PropertyTypes...>::input' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple).input(in);
}

template<typename ... PropertyTypes>
template<typename PropertyType, typename ostream_type>
bool PhysicalEntityModel<PropertyTypes...>::output(ostream_type & out) const
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'PhysicalEntityModel<PropertyTypes...>::output' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple).output(out);
}

// ----- Set and get property -----
template<typename ... PropertyTypes>
template<typename PropertyType, typename ValueType>
void PhysicalEntityModel<PropertyTypes...>::set(const ValueType & value)
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, 
		"Template parameter for function 'PhysicalEntity<PropertyTypes...>::set' must be in template parameter list in the specialization of 'PhysicalEntity'");

	this->template property<PropertyType>().set(value);
}

template<typename ... PropertyTypes>
template<typename PropertyType>
typename PropertyType::ValueType PhysicalEntityModel<PropertyTypes...>::get() const
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, 
		"Template parameter for function 'PhysicalEntity<PropertyTypes...>::get' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return this->template property<PropertyType>().get();
}

// ----- Check whether a property was assigned -----
template<typename ... PropertyTypes>
template<typename PropertyType>
bool PhysicalEntityModel<PropertyTypes...>::assigned() const
{
	static_assert(type_list<PropertyTypes...>::template contains<PropertyType>, "Template parameter for function 'assigned' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple).assigned();
}

#endif
