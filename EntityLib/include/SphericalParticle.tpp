#ifndef SPHERICAL_PARTICLE_TPP
#define SPHERICAL_PARTICLE_TPP

#include <Mathematics.hpp>

namespace psin {

template<typename...Prs>
void from_json(const json& j, SphericalParticle<Prs...> & p)
{
	p = SphericalParticle<Prs...>( j.get<typename SphericalParticle<Prs...>::BaseParticle>() );
}

template<typename...Prs>
void to_json(json& j, const SphericalParticle<Prs...> & p)
{
	typename SphericalParticle<Prs...>::BaseParticle base = p;
	j = base;
}

template<typename...Ts>
struct NamedType<SphericalParticle<Ts...>>
{
	const static std::string name;
}; //struct NamedType

template<typename...Ts>
const string NamedType<SphericalParticle<Ts...>>::name = "SphericalParticle";

template<typename...Ts, typename...Us>
Vector3D normalVersor(const SphericalParticle<Ts...> & lhs, const SphericalParticle<Us...> & rhs)
{
	return (rhs.getPosition() - lhs.getPosition()).normalized();
}

template<typename...Ts, typename...Us>
Vector3D normalVersor(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs)
{
	auto planeNormalVersor = rhs.getNormalVersor();

	return - signum(dot(lhs.getPosition()-rhs.getOrigin(), planeNormalVersor)) * planeNormalVersor;
}

template<typename...Ts, typename...Us>
double distance(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs)
{
	const auto position = lhs.getPosition();
	const auto origin = rhs.getOrigin();
	const auto normalVersor = rhs.getNormalVersor();

	return (position-origin).projectOn(normalVersor).length();
}

template<typename...Ts, typename...Us>
bool touch(const SphericalParticle<Ts...> & left, const SphericalParticle<Us...> & right)
{
	double radius1 = left.template get<Radius>();
	double radius2 = right.template get<Radius>();

	return (distance(left, right) <= radius1 + radius2);
}

template<typename...Ts, typename...Us>
bool touch(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs)
{
	return lhs.template get<Radius>() >= distance(lhs, rhs);
}

template<typename...Ts, typename...Us>
double overlap(const SphericalParticle<Ts...> & left, const SphericalParticle<Us...> & right)
{
	double radius1 = left.template get<Radius>();
	double radius2 = right.template get<Radius>();
	double dist = distance(left, right);
	double overlap = 0;

	if(dist <= radius1 + radius2)
	{
		overlap = radius1 + radius2 - dist;
	}

	return overlap;
}

template<typename...Ts, typename...Us>
double overlap(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs)
{
	if(touch(lhs, rhs))
	{
		return lhs.template get<Radius>() - distance(lhs, rhs);
	}
	else
	{
		return 0;
	}
}

template<typename...Ts, typename...Us>
double overlapDerivative(const SphericalParticle<Ts...> & left, const SphericalParticle<Us...> & right)
{
	if(touch(left, right))
	{
		const Vector3D positionDifference = right.getPosition() - left.getPosition();
		const Vector3D velocityDifference = right.getVelocity() - left.getVelocity();
		const double overlapDerivative = - dot(positionDifference, velocityDifference) / positionDifference.length();
		return overlapDerivative;
	}
	else
	{
		return 0;
	}
}

template<typename...Ts, typename...Us>
double overlapDerivative(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs)
{
	if(touch(lhs, rhs))
	{
		const auto position = lhs.getPosition();
		const auto velocity = lhs.getVelocity();
		const auto origin = rhs.getOrigin();
		const auto normalVersor = rhs.getNormalVersor();
		
		if( dot(position-origin, normalVersor) >= 0 )
		{
			return - dot(velocity, normalVersor);
		}
		else
		{
			return dot(velocity, normalVersor);
		}
	}
	else
	{
		return 0;
	}
}

template<typename...Ts, typename...Us>
Vector3D contactRadialVector(const SphericalParticle<Ts...> & lhs, const SphericalParticle<Us...> & rhs)
{
	if( touch(lhs, rhs) )
	{
		const double radius1 = lhs.template get<Radius>();
		const double radius2 = rhs.template get<Radius>();

		const double distance = psin::distance(lhs, rhs);

		const double contactPointRadius = ( (radius1*radius1) - (radius2*radius2) + (distance*distance) ) / ( 2 * distance );

		return contactPointRadius * psin::normalVersor(lhs, rhs);
	}
	else
	{
		throw std::runtime_error("Error in contactRadialVector(SphericalParticle, SphericalParticle): Particles that do not touch each other do not have a contactPoint.");
	}
}

template<typename...Ts, typename...Us>
Vector3D contactRadialVector(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs)
{
	if( touch(lhs, rhs) )
	{
		return (rhs.getOrigin() - lhs.getPosition()).projectOn(psin::normalVersor(lhs, rhs));
	}
	else
	{
		throw std::runtime_error("Error in contactRadialVector(SphericalParticle, FixedInfinitePlane): Elements that do not touch each other do not have a contactPoint.");
	}
}

template<typename...Ts, typename...Us>
Vector3D contactPoint(const SphericalParticle<Ts...> & lhs, const SphericalParticle<Us...> & rhs)
{
	if( touch(lhs, rhs) )
	{
		return contactRadialVector(lhs, rhs) + lhs.getPosition();
	}
	else
	{
		throw std::runtime_error("Error in contactPoint(SphericalParticle, SphericalParticle): Particles that do not touch each other do not have a contactPoint.");
	}
}

template<typename...Ts, typename...Us>
Vector3D relativeVelocityContactPoint(const SphericalParticle<Ts...> & lhs, const SphericalParticle<Us...> & rhs)
{
	return rhs.getVelocity() - lhs.getVelocity() 
		+ cross(rhs.getAngularVelocity(), contactRadialVector(rhs, lhs)) 
		- cross(lhs.getAngularVelocity(), contactRadialVector(lhs, rhs));
}

template<typename...Ts, typename...Us>
Vector3D relativeVelocityContactPoint(const SphericalParticle<Ts...> & lhs, const FixedInfinitePlane<Us...> & rhs)
{
	return - lhs.getVelocity() - cross(lhs.getAngularVelocity(), contactRadialVector(lhs, rhs));
}

template<typename T, typename U>
double relativeNormalSpeedContactPoint(const T & lhs, const U & rhs)
{
	return dot(relativeVelocityContactPoint(lhs, rhs), normalVersor(lhs, rhs));
}

template<typename T, typename U>
Vector3D relativeNormalVelocityContactPoint(const T & lhs, const U & rhs)
{
	return relativeNormalSpeedContactPoint(lhs, rhs) * normalVersor(lhs, rhs);
}

template<typename T, typename U>
Vector3D relativeTangentialVelocityContactPoint(const T & lhs, const U & rhs)
{
	return relativeVelocityContactPoint(lhs, rhs) - relativeNormalVelocityContactPoint(lhs, rhs);
}


// // ------------------------------- Constructor -------------------------------
template<typename ... PropertyTypes>
SphericalParticle<PropertyTypes...>::SphericalParticle(const BaseParticle & base)
	: BaseParticle(base)
{}

template<typename ... PropertyTypes>
SphericalParticle<PropertyTypes...>::SphericalParticle(const string & name, const int taylorOrder)
	: BaseParticle(name, taylorOrder)
{}

// // ------------------------------- Collision detector -------------------------------
template<typename ... PropertyTypes>
template<typename ... Us>
Vector3D SphericalParticle<PropertyTypes...>::relativeTangentialVelocity(const SphericalParticle<Us...> & neighbor) const
{
	// const Vector3D normalVersor = this->normalVersor( neighbor );
	// const Vector3D velocityDifference = neighbor.getVelocity() - this->getVelocity();
	// const Vector3D contact = contactPoint(*this, neighbor);

	// const Vector3D relativeTangentialCenterVelocity = velocityDifference - dot(velocityDifference, normalVersor) * normalVersor;
	// const Vector3D relativeTangentialRotationalVelocity =	cross(neighbor.getAngularVelocity(), contact - neighbor.getPosition()) -
	// 														cross(this->getAngularVelocity(), contact - this->getPosition());

	// const Vector3D relativeTangentialVelocity = relativeTangentialCenterVelocity + relativeTangentialRotationalVelocity;

	// return relativeTangentialVelocity;
	return relativeTangentialVelocityContactPoint(*this, neighbor);
}

template<typename ... PropertyTypes>
template<typename ... Us>
Vector3D SphericalParticle<PropertyTypes...>::tangentialVersor(const SphericalParticle<Us...> & neighbor) const
{
	const Vector3D relativeTangentialVelocity = this->relativeTangentialVelocity( neighbor );
	const double relativeTangentialVelocityLength = relativeTangentialVelocity.length();

	if(relativeTangentialVelocityLength > 0)
	{
		return relativeTangentialVelocity / relativeTangentialVelocityLength;
	}
	else
	{
		return nullVector3D();
	}
}

template<typename ... PropertyTypes>
template<typename ... Us>
Vector3D SphericalParticle<PropertyTypes...>::normalVersor(const SphericalParticle<Us...> & neighbor) const
{
	return psin::normalVersor(*this, neighbor);
}

} // psin

#endif
