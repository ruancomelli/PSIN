#include <vectorIO.hpp>



std::ostream & operator << (std::ostream & stream, const Vector3D & v){
	stream << v.x() << "    " << v.y() << "    " << v.z() << std::endl;
	return stream;
}

std::istream & operator >> (std::istream & stream, Vector3D & v){
	stream >> v.x();
	stream >> v.y();
	stream >> v.z();

	return stream;
}


std::ofstream & operator << (std::ofstream & stream, const Vector3D & v){
	stream << v.x() << "    " << v.y() << "    " << v.z() << std::endl;
	return stream;
}

std::ifstream & operator >> (std::ifstream & stream, Vector3D & v){
	stream >> v.x();
	stream >> v.y();
	stream >> v.z();

	return stream;
}