#ifndef SPHERE_H
#define SPHERE_H

#include <stdexcept>

class Sphere
{
	public:
		Sphere();
		virtual ~Sphere();

		void setRadius( double radius );
		double getRadius( void );

		double getSurfaceArea( void );
		double getVolume( void );
		
	private:
		double radius;
};

typedef SharedPointer< Sphere > SpherePtr;

#endif
