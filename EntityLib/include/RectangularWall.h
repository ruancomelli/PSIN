#ifndef RECTANGULAR_WALL_H
#define RECTANGULAR_WALL_H

// Standard
#include <array>

// EntityLib
#include <Boundary.h>

// UtilsLib
#include <SharedPointer.h>
#include <Vector3D.h>

class RectangularWall : public Boundary
{
	// using RectangularWallPtr = SharedPointer< RectangularWall >;
	// template<typename ... Args> using Array = std::Array<Args...>;

	// public:


	// 	// Spatial
	// 	Vector3D getNormalVersor();

	// private:
	// 	Array< Vector3D, 4 > vertex;
}; // class Boundary

using RectangularWallPtr = SharedPointer< RectangularWall >;

#endif
