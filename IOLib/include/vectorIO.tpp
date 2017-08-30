#ifndef VECTOR_IO_TPP
#define VECTOR_IO_TPP

namespace psin {

template <class type> 
std::ostream & operator<<( std::ostream & outputFile , const vector<type> & v){
	for( const type & entry : v )
	{
		outputFile << entry << std::endl;
	}

	return outputFile;
}

template <class type> 
std::istream & operator>>( std::istream & inputFile , vector<type> & v){
	for( type & entry : v ){
		inputFile >> entry;
	}

	return inputFile;
}

template <class type> 
std::ofstream & operator<<( std::ofstream & outputFile , const vector<type> & v){
	for( const type & entry : v ){
		outputFile << entry << std::endl;
	}

	return outputFile;
}

template <class type> 
std::ifstream & operator>>( std::ifstream & inputFile , vector<type> & v){
	for( type & entry : v ){
		inputFile >> entry;
	}

	return inputFile;
}

} // psin

#endif
