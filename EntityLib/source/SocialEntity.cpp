#include <SocialEntity.hpp>

namespace psin {

SocialEntity::SocialEntity()
	: HandledEntity()
{
}

SocialEntity::SocialEntity(const int handle)
	: HandledEntity(handle)
{
}

void SocialEntity::addNeighbor(const SocialEntity &  newNeighbor)
{
	this->neighborhood.insert(newNeighbor.getHandle());
}

void SocialEntity::removeNeighbor(const SocialEntity & neighbor)
{
	this->neighborhood.erase(neighbor.getHandle());
}

std::set<int> SocialEntity::getNeighborhood(void) const
{ 
	return this->neighborhood; 
}

} // psin
