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

} // psin

#endif