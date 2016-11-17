// Standard
#include <fstream>
#include <iostream>

// EntityLib
#include <Entity.h>

Entity readEntity( const string & fileName ){
	Entity entity;
	
	// ----- Initialize -----
	if( !fExist( fileName ) ) {
		cerr << "\nThere is no file " << fileName << " in the working area" << endl;
		exit(EXIT_FAILURE);
	}
	
	char buffer[800] = "NULL";
	ifstream file( problemfile.c_str() );

	// ----- Read Handle -----
	int handle;

	file.seekg( 0, ios::beg ); 
	while( strcmp( buf, "<Handle>" ) && !file.eof() ) file >> buf;
	if( file.eof() ){ cerr << "There is no handle in the file" << endl;
	file >> handle;

	entity.setHandle(handle);

	return entity;
}

bool fExist( string & filename ) {
	struct stat buffer;
	if ( stat( filename.c_str(), &buffer ) == 0 ) return true;
	return false;
}
