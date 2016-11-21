#include <readPhysicalEntity.h>

PhysicalEntity readPhysicalEntity( string & fileName )
{/*
	// ----- Read Entity -----
	Entity entity = readEntity(fileName);
	
	// ----- Initialize -----
	
	char buffer[800] = "NULL";
	ifstream file( fileName.c_str() );

	if( file.fail() ) {
		cerr << "\nThere is no file " << fileName << " in the working area" << endl;
		cout << "Hi";
		exit(EXIT_FAILURE);
	}

	// ----- Read taylorOrder -----
	int taylorOrder;

	file.seekg( 0, ios::beg ); 
	while( strcmp( buffer, "<TaylorOrder>" ) && !file.eof() ) file >> buffer;

	if( file.eof() )
	{ 
		cerr << "There is no <TaylorOrder> in the file" << endl; 
		taylorOrder = 3;
	}
	else
	{
		file >> taylorOrder;
	}

	// ----- Read dimension -----
	int dimension;

	file.seekg( 0, ios::beg ); 
	while( strcmp( buffer, "<Dimension>" ) && !file.eof() ) file >> buffer;

	if( file.eof() )
	{ 
		cerr << "There is no <Dimension> in the file" << endl;
		dimension = 3;
	}
	else
	{
		file >> dimension;
	}


	PhysicalEntity physicalEntity( taylorOrder, dimension, entity );

	return physicalEntity;*/

	return PhysicalEntity(4, 3, 3);
}