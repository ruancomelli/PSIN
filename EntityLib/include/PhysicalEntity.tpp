#ifndef PHYSICAL_ENTITY_TPP
#define PHYSICAL_ENTITY_TPP

// UtilsLib
#include <type_is_in_list.hpp>

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
	static_assert(type_is_in_list<PropertyType, PropertyTypes...>::value, "Template parameter for function 'property' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple);
}

template<typename ... PropertyTypes>
template<typename PropertyType>
PropertyType PhysicalEntityModel<PropertyTypes...>::property() const
{
	static_assert(type_is_in_list<PropertyType, PropertyTypes...>::value, "Template parameter for function 'property' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple);
}

// ----- Input and output property -----
template<typename ... PropertyTypes>
template<typename PropertyType>
bool PhysicalEntityModel<PropertyTypes...>::input(std::istream & in)
{
	static_assert(type_is_in_list<PropertyType, PropertyTypes...>::value, "Template parameter for function 'input' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple).input(in);
}

template<typename ... PropertyTypes>
template<typename PropertyType>
bool PhysicalEntityModel<PropertyTypes...>::output(std::ostream & out) const
{
	static_assert(type_is_in_list<PropertyType, PropertyTypes...>::value, "Template parameter for function 'output' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple).output(out);
}

// ----- Check whether a property was assigned -----
template<typename ... PropertyTypes>
template<typename PropertyType>
bool PhysicalEntityModel<PropertyTypes...>::assigned() const
{
	static_assert(type_is_in_list<PropertyType, PropertyTypes...>::value, "Template parameter for function 'assigned' must be in template parameter list in the specialization of 'PhysicalEntity'");

	return std::get<PropertyType>(this->propertyTuple).assigned();
}

#endif
