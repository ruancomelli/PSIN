#ifndef ENTITY_H
#define ENTITY_H

#include <stdexcept>

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

#endif
