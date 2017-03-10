#ifndef RAW_PROPERTY_CONTAINER_TPP
#define RAW_PROPERTY_CONTAINER_TPP

//	addProperty:
//		If argument's name is already in propertyName, its input and output methods are overwritten.
//		Otherwise, a new property is inserted.
template<typename InterfaceType, typename StoredType>
void RawPropertyContainer::addProperty(const Property<InterfaceType, StoredType> & property)
{
	string propertyName = property.getName();

	std::set<string>::iterator it = propertyNames->find( property.getName() );

	propertyNames->insert( propertyName );

	(*inputMethods)[propertyName] = property.inputMethod;
	(*outputMethods)[propertyName] = property.outputMethod;
}

#endif