// #ifndef FIXED_INFINITE_PLANE_H
// #define FIXED_INFINITE_PLANE_H

// // EntityLib
// #include <Boundary.hpp>

// // UtilsLib
// #include <SharedPointer.hpp>
// #include <Vector3D.hpp>

// class FixedInfinitePlane : public Boundary
// {
// 	using FixedInfinitePlanePtr = SharedPointer< FixedInfinitePlane >;

// 	public:
// 		// ---- Constructors ----
// 		FixedInfinitePlane(const Vector3D & origin, const Vector3D & normalVector);

// 		// Named Constructors
// 		static FixedInfinitePlane buildFromOriginAndTwoVectors(const Vector3D & origin, const Vector3D & vector1, const Vector3D & vector2);
// 		static FixedInfinitePlane buildFromThreePoints(const Vector3D & point1, const Vector3D & point2, const Vector3D & point3);

// 		// ---- Spatial ----
// 		Vector3D getNormalVersor() const;
// 		Vector3D getOrigin() const;

// 		bool containsPoint(const Vector3D & point) const; // Yields true iff point is contained in this plane [ Is (point - origin) perpendicular to normalVersor? ]
// 		bool containsVector(const Vector3D & v) const; // Yields true iff point is contained in this plane [ Is v perpendicular to normalVersor? ]

// 	private:
// 		Vector3D origin;
// 		Vector3D normalVersor;
// }; // class FixedInfinitePlane

// using FixedInfinitePlanePtr = SharedPointer< FixedInfinitePlane >;

// bool operator==(const FixedInfinitePlane & left, const FixedInfinitePlane & right);

// #endif
