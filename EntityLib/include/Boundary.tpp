#ifndef BOUNDARY_TPP
#define BOUNDARY_TPP

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
void Boundary<PropertyTypes...>::updatePosition(double t)
{
	this->setPositionMatrix( this->positionFunction(t) );
}

template<typename ... PropertyTypes>
void Boundary<PropertyTypes...>::updateOrientation(double t)
{
	this->setOrientationMatrix( this->orientationFunction(t) );
}

#endif