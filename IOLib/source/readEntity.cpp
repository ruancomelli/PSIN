#include <readEntity.h>

Entity readEntity( string & fileName ){
	FileReader fileReader(fileName);

	// ----- Read Handle -----
	int handle;
	fileReader.readValue("<Handle>", handle);

	return Entity(handle);
}