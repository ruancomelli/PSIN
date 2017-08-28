#ifndef HANDLED_ENTITY_HPP
#define HANDLED_ENTITY_HPP

#define DEFAULT_HANDLED_ENTITY_HANDLE -1

namespace psin {

class HandledEntity
{
	public:
		HandledEntity(void);
		explicit HandledEntity(const int handle );

		virtual ~HandledEntity();
		
		void setHandle(const int handle);
		int getHandle(void) const;
		
	private:
		int handle;
};

bool operator==( const HandledEntity & left, const HandledEntity & right );

} // psin

#endif
