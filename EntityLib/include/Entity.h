#ifndef ENTITY_H
#define ENTITY_H

// Standard
#include <stdexcept>

// UtilsLibSpecific
#include <SharedPointer.h>

class Entity
{
	public:
		Entity(const int handle = -1 );
		virtual ~Entity();
		
		void setHandle(const int handle);
		int getHandle(void) const;
		
	private:
		int handle;
};

bool operator==( const Entity & left, const Entity & right );

typedef SharedPointer<Entity> EntityPtr;

#endif
