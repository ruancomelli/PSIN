#ifndef FIXED_INFINITE_PLANE_TPP
#define FIXED_INFINITE_PLANE_TPP

// Standard
#include <stdexcept>



// ---- Constructors ----
template<typename ... PropertyTypes>
FixedInfinitePlane<PropertyTypes...>::FixedInfinitePlane(const Vector3D & origin, const Vector3D & normalVector)
	: origin(origin)
{
	if(normalVector == nullVector3D())
	{
		throw std::runtime_error("\nA FixedInfinitePlane cannot be initialized using a null normal vector\n");
	}
	else
	{
		this->normalVersor = normalVector.normalized();
	}
}

template<typename ... PropertyTypes>
FixedInfinitePlane<PropertyTypes...> FixedInfinitePlane<PropertyTypes...>::buildFromOriginAndTwoVectors(const Vector3D & origin, const Vector3D & vector1, const Vector3D & vector2)
{
	const Vector3D normalVector = cross(vector1, vector2);

	if(normalVector == nullVector3D())
	{
		throw std::runtime_error("\nA FixedInfinitePlane cannot be initialized using parallel or null vectors\n");
	}
	
	return FixedInfinitePlane(origin, normalVector);
}

template<typename ... PropertyTypes>
FixedInfinitePlane<PropertyTypes...> FixedInfinitePlane<PropertyTypes...>::buildFromThreePoints(const Vector3D & point1, const Vector3D & point2, const Vector3D & point3)
{
	const Vector3D vector1 = point2 - point1;
	const Vector3D vector2 = point3 - point1;

	const Vector3D normalVector = cross(vector1, vector2);

	if(normalVector == nullVector3D())
	{
		throw std::runtime_error("\nA FixedInfinitePlane cannot be initialized using colinear or coincident points\n");
	}
	
	return FixedInfinitePlane(point1, normalVector);
}

// ---- Spatial ----
template<typename ... PropertyTypes>
Vector3D FixedInfinitePlane<PropertyTypes...>::getNormalVersor() const
{
	return this->normalVersor;
}

template<typename ... PropertyTypes>
Vector3D FixedInfinitePlane<PropertyTypes...>::getOrigin() const
{
	return this->origin;
}


template<typename ... PropertyTypes>
bool FixedInfinitePlane<PropertyTypes...>::containsPoint(const Vector3D & point) const
{
	const Vector3D v = point - this->origin;
	return this->containsVector(v);
}

template<typename ... PropertyTypes>
bool FixedInfinitePlane<PropertyTypes...>::containsVector(const Vector3D & v) const
{
	return dot(v, this->normalVersor) < VECTOR_3D_EQUAL_TOLERANCE ? true : false;
}


// ---- Compare ----

// bool operator==(const FixedInfinitePlane<PropertyTypes...> & left, const FixedInfinitePlane<PropertyTypes...> & right)
//	Two 2D-planes are equal if, and only if, the following two assertions yield true:
//		1) Their normal versors are equal or opposite. This means that the planes are parallel
//		2) Both planes contain at least one point in common.
template<typename ... PropertyTypes>
bool operator==(const FixedInfinitePlane<PropertyTypes...> & left, const FixedInfinitePlane<PropertyTypes...> & right)
{
	Vector3D leftOrigin = left.getOrigin();
	Vector3D rightOrigin = right.getOrigin();

	bool parallel = parallelPlanes(left, right);
	bool containSamePoint = left.containsPoint( right.getOrigin() );

	return parallel && containSamePoint;
}

template<typename Plane1, typename Plane2>
bool parallelPlanes(const Plane1 & left, const Plane2 & right)
{
	Vector3D leftVersor = left.getNormalVersor();
	Vector3D rightVersor = right.getNormalVersor();

    return ( leftVersor == rightVersor ) || ( leftVersor == - rightVersor );
}

#endif