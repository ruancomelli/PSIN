#include <Entity.h>

// Constructor
Entity::Entity(const int handle)
{
	setHandle(handle);
}

// Destructor
Entity::~Entity()
{
}

void Entity::setHandle(const int handle)
{
	if(handle > 0)
	{
		this->handle = handle;
	}
	else
	{
		throw std::runtime_error("Invalid handle inserted.");
	}
	
	return;
}

int Entity::getHandle(void) const
{
	return this->handle;
}
