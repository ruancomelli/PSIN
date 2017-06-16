// ----- Constructors -----
#include <iostream>

template<typename T>
PositiveProperty<T>::PositiveProperty()
{}

template<typename T>
PositiveProperty<T>::PositiveProperty(const T & value)
{
	this->set(value);
}


// Set and get value
template<typename T>
template<typename U>
void PositiveProperty<T>::set(const U & value)
{
	if(value > 0)
	{
		this->assign(value);
	}
	else
	{
		std::cerr << "Error: value to set must be positive.";
		this->assignedFlag = false;
	}
}