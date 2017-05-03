#include <SocialEntity.hpp>

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
