// ----- Constructors -----
template<typename type>
PositiveProperty<type>::PositiveProperty()
{}

template<typename type>
PositiveProperty<type>::PositiveProperty(const type & value)
{
	this->set(value);
}


// Set and get value
template<typename type>
void PositiveProperty<type>::set(const type & value)
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