#ifndef FIXED_INFINITE_PLANE_HPP
#define FIXED_INFINITE_PLANE_HPP

// EntityLib
#include <FixedBoundary.hpp>

// UtilsLib
#include <Vector3D.hpp>

namespace psin {

template<typename ... PropertyTypes>
class FixedInfinitePlane : public FixedBoundary<PropertyTypes...>
{
	public:
		// ---- Constructors ----
		FixedInfinitePlane(const Vector3D & origin, const Vector3D & normalVector);

		// Named Constructors
		static FixedInfinitePlane<PropertyTypes...> buildFromOriginAndTwoVectors(const Vector3D & origin, const Vector3D & vector1, const Vector3D & vector2);
		static FixedInfinitePlane<PropertyTypes...> buildFromThreePoints(const Vector3D & point1, const Vector3D & point2, const Vector3D & point3);

		// ---- Spatial ----
		Vector3D getNormalVersor() const;
		Vector3D getOrigin() const;

		bool containsPoint(const Vector3D & point) const; // Yields true iff point is contained in this plane [ Is (point - origin) perpendicular to normalVersor? ]
		bool containsVector(const Vector3D & v) const; // Yields true iff point is contained in this plane [ Is v perpendicular to normalVersor? ]

	private:
		Vector3D origin;
        Vector3D normalVersor;
};

template<typename ... PropertyTypes>
bool operator==(const FixedInfinitePlane<PropertyTypes...> & left, const FixedInfinitePlane<PropertyTypes...> & right);

template<typename Plane1, typename Plane2>
bool parallelPlanes(const Plane1 & left, const Plane2 & right);

} // psin

#include <FixedInfinitePlane.tpp>

#endif
