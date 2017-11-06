// ----- Constructors -----
#include <iostream>

namespace psin {
	
template<typename T>
NonNegativeProperty<T>::NonNegativeProperty()
{}

template<typename T>
NonNegativeProperty<T>::NonNegativeProperty(const T & value)
{
	this->set(value);
}


// Set and get value
template<typename T>
template<typename U>
void NonNegativeProperty<T>::set(const U & value)
{
	if(value >= 0)
	{
		this->assign(value);
	}
	else
	{
		std::cerr << "Error: value to set must be positive.";
		this->assignedFlag = false;
	}
}

} // psin
