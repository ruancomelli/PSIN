#ifndef SPHERICAL_PARTICLE_TPP
#define SPHERICAL_PARTICLE_TPP

template<typename ... Args>
bool touch(const SphericalParticle<Args...> & left, const SphericalParticle<Args...> & right)
{
	using Radius = PropertyDefinitions::Radius;

	double radius1 = left.template property<Radius>().get();
	double radius2 = right.template property<PropertyDefinitions::Radius>().get();

	return distance(left, right) <= radius1 + radius2;
}

template<typename ... Args>
double overlap(const SphericalParticle<Args...> & left, const SphericalParticle<Args...> & right)
{
	using Radius = PropertyDefinitions::Radius;

	double radius1 = left.template property<Radius>().get();
	double radius2 = right.template property<PropertyDefinitions::Radius>().get();
	double dist = distance(left, right);
	double overlap = 0;

	if(dist <= radius1 + radius2)
	{
		overlap = radius1 + radius2 - dist;
	}

	return overlap;
}

template<typename ... Args>
double overlapDerivative(const SphericalParticle<Args...> & left, const SphericalParticle<Args...> & right)
{
	if(touch(left, right))
	{
		const Vector3D positionDifference = right->getPosition() - left->getPosition();
		const Vector3D velocityDifference = right->getVelocity() - left->getVelocity();
		const double overlapDerivative = - dot(positionDifference, velocityDifference) / positionDifference.length();
		return overlapDerivative;
	}
	else
	{
		return 0;
	}
}

template<typename ... Args>
Vector3D contactPoint(const SphericalParticle<Args...> & left, const SphericalParticle<Args...> & right)
{
	if( touch(left, right ) )
	{
		const double radius1 = left.template property<PropertyDefinitions::Radius>().get();
		const double radius2 = right.template property<PropertyDefinitions::Radius>().get();

		const double distance = ::distance(left, right);

		const double contactPointSize = ( (radius1*radius1) - (radius2*radius2) + (distance*distance) ) / ( 2 * distance );	// See law of cosines
		const Vector3D contactPoint = contactPointSize * left.normalDirection( right ) + left.getPosition();

		return contactPoint;
	}
	else
	{
		throw std::runtime_error("Error in contactPoint(SphericalParticle, SphericalParticle): Particles that do not touch each other do not have a contactPoint.");
	}
}


// // ------------------------------- Constructor -------------------------------
template<typename ... PropertyTypes>
SphericalParticle<PropertyTypes...>::SphericalParticle()
	: BaseParticle()
{}

template<typename ... PropertyTypes>
SphericalParticle<PropertyTypes...>::SphericalParticle(const int taylorOrder, const int dimension, const int handle)
	: BaseParticle(taylorOrder, dimension, handle)
{}

template<typename ... PropertyTypes>
SphericalParticle<PropertyTypes...>::SphericalParticle(const BaseParticle & base)
	: BaseParticle(base)
{}

// // ------------------------------- Collision detector -------------------------------
template<typename ... PropertyTypes>
Vector3D SphericalParticle<PropertyTypes...>::relativeTangentialVelocity( const SphericalParticle<PropertyTypes...> & neighbor ) const
{
	const Vector3D normalVersor = this->normalVersor( neighbor );
	const Vector3D velocityDifference = neighbor->getVelocity() - this->getVelocity();
	const Vector3D contactPoint = contactPoint(*this, neighbor);

	const Vector3D relativeTangentialCenterVelocity = velocityDifference - dot(velocityDifference, normalVersor) * normalVersor;
	const Vector3D relativeTangentialRotationalVelocity =	cross(neighbor->getAngularVelocity(), contactPoint - neighbor->getPosition()) -
															cross(this->getAngularVelocity(), contactPoint - this->getPosition());

	const Vector3D relativeTangentialVelocity = relativeTangentialCenterVelocity + relativeTangentialRotationalVelocity;

	return relativeTangentialVelocity;
}

template<typename ... PropertyTypes>
Vector3D SphericalParticle<PropertyTypes...>::tangentialVersor( const SphericalParticle<PropertyTypes...> & neighbor ) const
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

#endif
