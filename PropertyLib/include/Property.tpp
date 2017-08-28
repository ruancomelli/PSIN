#ifndef PROPERTY_TPP
#define PROPERTY_TPP

namespace psin {

template<typename T>
Property<T>& Property<T>::operator=(const Property<T> & other)
{
	if(other.value)
	{
		this->value = make_unique<T>( *other.value );
	}
	this->assignedFlag = other.assignedFlag;

	return *this;
}

// ----- Constructors -----
template<typename T>
Property<T>::Property()
{}

template<typename T>
Property<T>::Property(const T & value)
{
	this->set(value);
}

template<typename T>
Property<T>::Property(const Property<T> & other)
	: assignedFlag(other.assignedFlag)
{
	if(other.value)
	{
		this->value = make_unique<T>( *other.value );
	}
}


// ----- Set and get value -----
template<typename T>
template<typename U>
void Property<T>::set(const U & value)
{
	this->assign(value);
}

template<typename T>
T Property<T>::get() const
{
	return *this->value;
}

// ----- Input and output value -----
template<typename T>
template<typename istream_type>
bool Property<T>::input(istream_type & in)
{
	T value;

	in >> value;

	this->assign(value);

	return true;
}

template<typename T>
template<typename ostream_type>
bool Property<T>::output(ostream_type & out) const
{
	out << *this->value;

	return true;
}

template<typename T>
void Property<T>::assign(const T & value)
{
	this->value = make_unique<T>(value);
	this->assignedFlag = true;
}

// ----- Assigned -----
template<typename T>
bool Property<T>::assigned() const
{
	return this->assignedFlag;
}


} // psin

#endif // PROPERTY_TPP
