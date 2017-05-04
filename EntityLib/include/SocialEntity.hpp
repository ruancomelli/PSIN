#ifndef SOCIAL_ENTITY_HPP
#define SOCIAL_ENTITY_HPP

// EntityLib
#include <HandledEntity.hpp>

// Standard
#include <set>

class SocialEntity : public HandledEntity
{
	public:
		SocialEntity();
		explicit SocialEntity(const int handle);

		void addNeighbor(const SocialEntity & newNeighbor);
		void removeNeighbor(const SocialEntity & newNeighbor);
		std::set<int> getNeighborhood(void) const;

	private:
		std::set<int> neighborhood;
};

#endif