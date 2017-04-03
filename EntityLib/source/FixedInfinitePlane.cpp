#include <FixedInfinitePlane.hpp>

// Standard
#include <stdexcept>



// ---- Constructors ----
FixedInfinitePlane::FixedInfinitePlane(const Vector3D & origin, const Vector3D & normalVector)
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

FixedInfinitePlane FixedInfinitePlane::buildFromOriginAndTwoVectors(const Vector3D & origin, const Vector3D & vector1, const Vector3D & vector2)
{
	const Vector3D normalVector = cross(vector1, vector2);

	if(normalVector == nullVector3D())
	{
		throw std::runtime_error("\nA FixedInfinitePlane cannot be initialized using parallel or null vectors\n");
	}
	
	return FixedInfinitePlane(origin, normalVector);
}

FixedInfinitePlane FixedInfinitePlane::buildFromThreePoints(const Vector3D & point1, const Vector3D & point2, const Vector3D & point3)
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
Vector3D FixedInfinitePlane::getNormalVersor() const
{
	return this->normalVersor;
}

Vector3D FixedInfinitePlane::getOrigin() const
{
	return this->origin;
}


bool FixedInfinitePlane::containsPoint(const Vector3D & point) const
{
	const Vector3D v = point - this->origin;
	return this->containsVector(v);
}

bool FixedInfinitePlane::containsVector(const Vector3D & v) const
{
	return dot(v, this->normalVersor) < VECTOR_3D_EQUAL_TOLERANCE ? true : false;
}


// ---- Compare ----

// bool operator==(const FixedInfinitePlane & left, const FixedInfinitePlane & right)
//	Two 2D-planes are equal if, and only if, the following two assertions yield true:
//		1) Their normal versors are equal or opposite. This means that the planes are parallel
//		2) Both planes contain at least one point in common.
bool operator==(const FixedInfinitePlane & left, const FixedInfinitePlane & right)
{
	Vector3D leftVersor = left.getNormalVersor();
	Vector3D rightVersor = right.getNormalVersor();
	Vector3D leftOrigin = left.getOrigin();
	Vector3D rightOrigin = right.getOrigin();

	bool equalVersors = ( leftVersor == rightVersor ) || ( leftVersor == - rightVersor );
	bool containSamePoint = left.containsPoint( right.getOrigin() );

	return equalVersors && containSamePoint;
}