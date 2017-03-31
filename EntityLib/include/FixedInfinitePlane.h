#ifndef FIXED_INFINITE_PLANE_H
#define FIXED_INFINITE_PLANE_H

// EntityLib
#include <Boundary.h>

// UtilsLib
#include <SharedPointer.h>
#include <Vector3D.h>

class FixedInfinitePlane : public Boundary
{
	using FixedInfinitePlanePtr = SharedPointer< FixedInfinitePlane >;

	public:
		// ---- Constructors ----
		FixedInfinitePlane(const Vector3D & origin, const Vector3D & normalVector);

		// Named Constructors
		static FixedInfinitePlane buildFromOriginAndTwoVectors(const Vector3D & origin, const Vector3D & vector1, const Vector3D & vector2);
		static FixedInfinitePlane buildFromThreePoints(const Vector3D & point1, const Vector3D & point2, const Vector3D & point3);

		// ---- Spatial ----
		Vector3D getNormalVersor();

	private:
		Vector3D origin;
		Vector3D normalVersor;
}; // class FixedInfinitePlane

using FixedInfinitePlanePtr = SharedPointer< FixedInfinitePlane >;

#endif
