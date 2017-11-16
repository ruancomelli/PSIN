#ifndef FIXED_INFINITE_PLANE_TPP
#define FIXED_INFINITE_PLANE_TPP

// UtilsLib
#include <NamedType.hpp>

// Standard
#include <stdexcept>

namespace nlohmann {

template<typename ... PropertyTypes>
struct adl_serializer< psin::FixedInfinitePlane<PropertyTypes...> > {

	static psin::FixedInfinitePlane<PropertyTypes...> from_json(const json& j) {
		typename psin::FixedInfinitePlane<PropertyTypes...>::BaseFixedBoundary base = j;

		if(j.count("origin") > 0
			and j.count("normalVector") > 0)
		{
			return psin::FixedInfinitePlane<PropertyTypes...>(
					j.at("origin").get<psin::Vector3D>(),
					j.at("normalVector").get<psin::Vector3D>(),
					base
				);
		}
		else if(j.count("origin") > 0
			and j.count("vector1") > 0
			and j.count("vector2") > 0)
		{
			return psin::FixedInfinitePlane<PropertyTypes...>::buildFromOriginAndTwoVectors(
					j.at("origin").get<psin::Vector3D>(),
					j.at("vector1").get<psin::Vector3D>(),
					j.at("vector2").get<psin::Vector3D>(),
					base
				);
		}
		else if(j.count("point1") > 0
			and j.count("point2") > 0
			and j.count("point3") > 0)
		{
			return psin::FixedInfinitePlane<PropertyTypes...>::buildFromThreePoints(
					j.at("point1").get<psin::Vector3D>(),
					j.at("point2").get<psin::Vector3D>(),
					j.at("point3").get<psin::Vector3D>(),
					base
				);
		}
	}

	static void to_json(json& j, const psin::FixedInfinitePlane<PropertyTypes...> & fplane) {
		json jp = json{
			{"Origin", fplane.getOrigin()},
			{"NormalVersor", fplane.getNormalVersor()}
		};
		typename psin::FixedInfinitePlane<PropertyTypes...>::BaseFixedBoundary base = fplane;
		json jb = base;
		j = psin::merge(jp, jb);
	}

};

} // nlohmann

namespace psin {

template<typename...Ts>
struct NamedType<FixedInfinitePlane<Ts...>>
{
	const static std::string name;
}; //struct NamedType

template<typename...Ts>
const string NamedType<FixedInfinitePlane<Ts...>>::name = "FixedInfinitePlane";

// ---- Constructors ----
template<typename ... PropertyTypes>
FixedInfinitePlane<PropertyTypes...>::FixedInfinitePlane(const Vector3D & origin, const Vector3D & normalVector, const BaseFixedBoundary & base)
	: origin(origin),
	BaseFixedBoundary(base)
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
FixedInfinitePlane<PropertyTypes...> FixedInfinitePlane<PropertyTypes...>::buildFromOriginAndTwoVectors(const Vector3D & origin, const Vector3D & vector1, const Vector3D & vector2, const BaseFixedBoundary & base)
{
	const Vector3D normalVector = cross(vector1, vector2);

	if(normalVector == nullVector3D())
	{
		throw std::runtime_error("\nA FixedInfinitePlane cannot be initialized using parallel or null vectors\n");
	}
	
	return FixedInfinitePlane(origin, normalVector, base);
}

template<typename ... PropertyTypes>
FixedInfinitePlane<PropertyTypes...> FixedInfinitePlane<PropertyTypes...>::buildFromThreePoints(const Vector3D & point1, const Vector3D & point2, const Vector3D & point3, const BaseFixedBoundary & base)
{
	const Vector3D vector1 = point2 - point1;
	const Vector3D vector2 = point3 - point1;

	const Vector3D normalVector = cross(vector1, vector2);

	if(normalVector == nullVector3D())
	{
		throw std::runtime_error("\nA FixedInfinitePlane cannot be initialized using colinear or coincident points\n");
	}
	
	return FixedInfinitePlane(point1, normalVector, base);
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

	return parallel and containSamePoint;
}

template<typename Plane1, typename Plane2>
bool parallelPlanes(const Plane1 & left, const Plane2 & right)
{
	Vector3D leftVersor = left.getNormalVersor();
	Vector3D rightVersor = right.getNormalVersor();

	return ( leftVersor == rightVersor ) or ( leftVersor == - rightVersor );
}

template<typename...Us>
Vector3D normalVersor(const SpatialEntity & s, const FixedInfinitePlane<Us...> & plane)
{
	return dot(plane.getOrigin() - s.getPosition(), plane.getNormalVersor()) > 0
		? plane.getNormalVersor()
		: -plane.getNormalVersor();
}

} // psin

#endif