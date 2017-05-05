#ifndef PROPERTY_TPP
#define PROPERTY_TPP


template<typename type>
Property<type>& Property<type>::operator=(const Property<type> & other)
{
	if(other.value)
	{
		this->value = makeUnique<type>( *other.value );
	}
	this->assignedFlag = other.assignedFlag;

	return *this;
}

// ----- Constructors -----
template<typename type>
Property<type>::Property()
{}

template<typename type>
Property<type>::Property(const type & value)
{
	this->set(value);
}

template<typename type>
Property<type>::Property(const Property<type> & other)
	: assignedFlag(other.assignedFlag)
{
	if(other.value)
	{
		this->value = makeUnique<type>( *other.value );
	}
}


// ----- Set and get value -----
template<typename type>
void Property<type>::assign(const type & value)
{
	this->value = makeUnique<type>(value);
	this->assignedFlag = true;
}

template<typename type>
void Property<type>::set(const type & value)
{
	this->assign(value);
}

template<typename type>
type Property<type>::get(void) const
{
	return *this->value;
}

// ----- Input and output property -----
template<typename type>
bool Property<type>::input(std::istream & in)
{
	type value;

	in >> value;

	this->assign(value);

	return true;
}

template<typename type>
bool Property<type>::output(std::ostream & out) const
{
	out << *this->value;

	return true;
}

// ----- Assigned -----
template<typename type>
bool Property<type>::assigned() const
{
	return this->assignedFlag;
}

#endif
