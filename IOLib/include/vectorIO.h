#ifndef VECTOR_IO_H
#define VECTOR_IO_H

// Standard
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

// UtilsLib
#include <Vector3D.h>

using std::vector;
using std::runtime_error;

template <class type> std::ostream & operator<<( std::ostream & outputFile , const vector<type> & v){
	for( unsigned i = 0 ; i < v.size() ; ++i){
		outputFile << v[i] << endl;
	}
	return outputFile;
}

template <class type> std::istream & operator>>( std::istream & inputFile , vector<type> & v){
	for( unsigned i = 0 ; ( i < v.size() ) && ( !inputFile.eof() ) && ( !inputFile.fail() ) ; ++i){
		inputFile >> v[i];
	}
	return inputFile;
}

template <class type> std::ofstream & operator<<( std::ofstream & outputFile , const vector<type> & v){
	for( unsigned i = 0 ; i < v.size() ; ++i){
		outputFile << v[i] << endl;
	}
	return outputFile;
}

template <class type> std::ifstream & operator>>( std::ifstream & inputFile , vector<type> & v){
	for( unsigned i = 0 ; ( i < v.size() ) && ( !inputFile.eof() ) && ( !inputFile.fail() ) ; ++i){
		inputFile >> v[i];
	}
	return inputFile;
}

ostream & operator << (ostream & stream, const Vector3D & v);
istream & operator >> (istream & stream, Vector3D & v);

ofstream & operator << (ofstream & stream, const Vector3D & v);
ifstream & operator >> (ifstream & stream, Vector3D & v);

#endif
