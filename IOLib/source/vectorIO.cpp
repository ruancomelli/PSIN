#include <vectorIO.h>

ostream & operator << (ostream & stream, const Vector3D & v){
	stream << v.x() << "    " << v.y() << "    " << v.z() << endl;
	return stream;
}

istream & operator >> (istream & stream, Vector3D & v){
	stream >> v.x();
	stream >> v.y();
	stream >> v.z();

	return stream;
}


ofstream & operator << (ofstream & stream, const Vector3D & v){
	stream << static_cast<long double>(v.x()) << "    " << static_cast<long double>(v.y()) << "    " << static_cast<long double>(v.z()) << endl;
	return stream;
}

ifstream & operator >> (ifstream & stream, Vector3D & v){
	stream >> v.x();
	stream >> v.y();
	stream >> v.z();

	return stream;
}