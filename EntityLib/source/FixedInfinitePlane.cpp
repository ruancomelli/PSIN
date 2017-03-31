#include <FixedInfinitePlane.h>

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