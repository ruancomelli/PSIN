#include <Entity.h>

// Constructor
Entity::Entity(const int handle) : handle(handle){}

// Destructor
Entity::~Entity()
{
}

void Entity::setHandle(const int handle)
{
	this->handle = handle;
}

int Entity::getHandle(void) const
{
	return this->handle;
}

bool operator==(Entity left, Entity right){
	return left.getHandle() == right.getHandle();
}
