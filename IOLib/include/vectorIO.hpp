#ifndef VECTOR_IO_HPP
#define VECTOR_IO_HPP

// Standard
#include <fstream>
#include <vector>

// UtilsLib
#include <Vector3D.hpp>

using std::vector;



template <class type> 
std::ostream & operator<<( std::ostream & outputFile , const vector<type> & v);

template <class type> 
std::istream & operator>>( std::istream & inputFile , vector<type> & v);

template <class type> 
std::ofstream & operator<<( std::ofstream & outputFile , const vector<type> & v);

template <class type> 
std::ifstream & operator>>( std::ifstream & inputFile , vector<type> & v);



std::ostream & operator << (std::ostream & stream, const Vector3D & v);
std::istream & operator >> (std::istream & stream, Vector3D & v);

std::ofstream & operator << (std::ofstream & stream, const Vector3D & v);
std::ifstream & operator >> (std::ifstream & stream, Vector3D & v);



#include <vectorIO.tpp>

#endif
