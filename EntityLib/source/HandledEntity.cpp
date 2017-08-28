#include <HandledEntity.hpp>

namespace psin {

// Constructor
HandledEntity::HandledEntity(void)
	: handle( DEFAULT_HANDLED_ENTITY_HANDLE )
{
}

HandledEntity::HandledEntity(const int handle) 
	: handle(handle)
{
}

// Destructor
HandledEntity::~HandledEntity()
{
}

void HandledEntity::setHandle(const int handle)
{
	this->handle = handle;
}

int HandledEntity::getHandle(void) const
{
	return this->handle;
}

bool operator==( const HandledEntity & left, const HandledEntity & right)
{
	return left.getHandle() == right.getHandle();
}

} // psin