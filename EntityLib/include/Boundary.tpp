#ifndef BOUNDARY_TPP
#define BOUNDARY_TPP

namespace psin {

template<typename ... PropertyTypes>
void Boundary<PropertyTypes...>::setPositionFunction( const std::function< Spatial(double)> & f )
{
	this->positionFunction = f;
}

template<typename ... PropertyTypes>
void Boundary<PropertyTypes...>::setOrientationFunction( const std::function< Spatial(double)> & f )
{
	this->orientationFunction = f;
}

template<typename ... PropertyTypes>
void Boundary<PropertyTypes...>::updatePosition(const double & t)
{
	this->setPositionMatrix( this->positionFunction(t) );
}

template<typename ... PropertyTypes>
void Boundary<PropertyTypes...>::updateOrientation(const double & t)
{
	this->setOrientationMatrix( this->orientationFunction(t) );
}

} // psin

#endif