#ifndef FIXED_BOUNDARY_TPP
#define FIXED_BOUNDARY_TPP

namespace psin {

template<typename ... PropertyTypes>
FixedBoundary<PropertyTypes...>::FixedBoundary(const Vector3D & position, const Vector3D & orientation)
{
    this->setPosition(position);
    this->setOrientation(orientation);
}

template<typename ... PropertyTypes>
void FixedBoundary<PropertyTypes...>::updatePosition(const double & t)
{}

template<typename ... PropertyTypes>
void FixedBoundary<PropertyTypes...>::updateOrientation(const double & t)
{}

} // psin

#endif
