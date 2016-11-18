#include <readEntity.h>

Entity readEntity( string & fileName ){
	Entity entity;
	
	// ----- Initialize -----
	
	char buffer[800] = "NULL";
	ifstream file( fileName.c_str() );

	if( file.fail() ) {
		cerr << "\nThere is no file " << fileName << " in the working area" << endl;
		cout << "Hi";
		exit(EXIT_FAILURE);
	}

	// ----- Read Handle -----
	int handle;

	file.seekg( 0, ios::beg ); 
	while( strcmp( buffer, "<Handle>" ) && !file.eof() ) file >> buffer;
	if( file.eof() ){ cerr << "There is no handle in the file" << endl; }
	file >> handle;

	entity.setHandle(handle);

	return entity;
}