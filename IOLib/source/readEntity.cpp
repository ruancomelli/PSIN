#include <readEntity.h>

EntityPtr readEntity( const string fileName ){
	FileReader fileReader(fileName);

	// ----- Read Handle -----
	int handle;
	fileReader.readValue("<Handle>", handle);

	return EntityPtr( new Entity(handle) );
}