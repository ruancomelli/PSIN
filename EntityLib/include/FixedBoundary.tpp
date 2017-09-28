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
template<typename Time>
void FixedBoundary<PropertyTypes...>::updatePosition(const Time & time) const
{}

template<typename ... PropertyTypes>
template<typename Time>
void FixedBoundary<PropertyTypes...>::updateOrientation(const Time & time) const
{}

} // psin

#endif
