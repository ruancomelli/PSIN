#ifndef ENTITY_H
#define ENTITY_H

// UtilsLib
#include <SharedPointer.hpp>

class Entity
{
	public:
		Entity(void);
		explicit Entity(const int handle );

		virtual ~Entity();
		
		void setHandle(const int handle);
		int getHandle(void) const;
		
	private:
		int handle;
};

bool operator==( const Entity & left, const Entity & right );

typedef SharedPointer<Entity> EntityPtr;

#endif
