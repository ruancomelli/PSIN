#include <readPhysicalEntity.h>

PhysicalEntity readPhysicalEntity( string & fileName )
{
	// ----- Read Entity -----
	Entity entity = readEntity(fileName);
	
	// ----- Initialize -----
	
	char buffer[800] = "NULL";
	ifstream file( fileName.c_str() );

	if( file.fail() ) {
		cerr << "\nThere is no file " << fileName << " in the working area" << endl;
		return PhysicalEntity();
	}

	// ----- Read taylorOrder -----
	int taylorOrder;

	file.clear();
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

	file.clear();
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

	return physicalEntity;
}