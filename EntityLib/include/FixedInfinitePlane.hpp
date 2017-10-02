#ifndef FIXED_INFINITE_PLANE_HPP
#define FIXED_INFINITE_PLANE_HPP

// EntityLib
#include <FixedBoundary.hpp>

// UtilsLib
#include <Vector3D.hpp>

namespace psin {

template<typename ... PropertyTypes>
class FixedInfinitePlane
	: public FixedBoundary<PropertyTypes...>
{
	public:
		using BaseFixedBoundary = FixedBoundary<PropertyTypes...>;

		constexpr static bool is_plane = true;
		
		// ---- ctors ----
		FixedInfinitePlane(const FixedInfinitePlane<PropertyTypes...> &) = default;
		FixedInfinitePlane(FixedInfinitePlane<PropertyTypes...> &&) = default;

		FixedInfinitePlane(const Vector3D & origin, const Vector3D & normalVector, const BaseFixedBoundary & base = BaseFixedBoundary());

		// Named Constructors
		static FixedInfinitePlane<PropertyTypes...> buildFromOriginAndTwoVectors(
			const Vector3D & origin, const Vector3D & vector1, const Vector3D & vector2, 
			const BaseFixedBoundary & base = BaseFixedBoundary()
			);

		static FixedInfinitePlane<PropertyTypes...> buildFromThreePoints(
			const Vector3D & point1, const Vector3D & point2, const Vector3D & point3, 
			const BaseFixedBoundary & base = BaseFixedBoundary()
			);

		// ---- Spatial ----
		Vector3D getNormalVersor() const;
		Vector3D getOrigin() const;

		bool containsPoint(const Vector3D & point) const; // Yields true iff point is contained in this plane [ is (point - origin) perpendicular to normalVersor? ]
		bool containsVector(const Vector3D & v) const; // Yields true iff point is contained in this plane [ is v perpendicular to normalVersor? ]

	private:
		Vector3D origin;
        Vector3D normalVersor;
};

template<typename T, typename SFINAE = void>
struct is_plane : std::false_type {};

template<typename T>
struct is_plane<
		T,
		std::enable_if_t<T::is_plane or not T::is_plane>
	>
	: mp::bool_constant<T::is_plane>
{};

template<typename ... PropertyTypes>
bool operator==(const FixedInfinitePlane<PropertyTypes...> & left, const FixedInfinitePlane<PropertyTypes...> & right);

template<typename Plane1, typename Plane2>
bool parallelPlanes(const Plane1 & left, const Plane2 & right);

} // psin

#include <FixedInfinitePlane.tpp>

#endif
