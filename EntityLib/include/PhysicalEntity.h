#ifndef PHYSICAL_ENTITY_H
#define PHYSICAL_ENTITY_H

#include <vector>

#include "Entity.h"
#include "Vector.h"

using namespace std;

enum GeometryType{
	SPHERE = 0
};

enum ScalarProperty{
	MASS = 0,
	MOMENT_OF_INERTIA,
	VOLUME,
	SPECIFIC_MASS,
	N_SCALAR_PROPERTY
};

enum VectorialProperty{
	N_VECTORIAL_PROPERTY
};

enum MatricialProperty{
	N_MATRICIAL_PROPERTY
};

class PhysicalEntity: public Entity
{
	public:
		// ---- Constructors ----
		PhysicalEntity();
		PhysicalEntity(const int order, const int dimension);
		PhysicalEntity(const int handle, const vector<double> scalarPropertyVector);

		// ---- Spatial localization ----
		void setPosition(const DoubleVector2D position);
		DoubleVector2D getPosition(void) const;
		DoubleVector getPosition(const int) const;
		
		void setOrientation(const DoubleVector2D orientation);
		DoubleVector2D getOrientation(void) const;
		DoubleVector getOrientation(const int derivate) const;
		
		// ---- Geometry ----
		void setGeometry(const GeometryType);
		GeometryType getGeometry() const;
		
		// ---- Properties ----
		void setScalarProperty(const int scalarPropertyIdentifier, const double scalarPropertyValue);
		void setScalarProperty(const DoubleVector scalarPropertyVector);
		double getScalarProperty(const int scalarPropertyIdentifier);
		DoubleVector getScalarProperty();
		
	private:
		static int taylorOrder; // number of derivates. If zero, there is just the position (not the velocity)
		static int dimension; // ( = 2 ) or ( = 3 )

		DoubleVector scalarProperty;
		DoubleVector2D vectorialProperty;
		vector < DoubleVector2D > matricialProperty;
		
		vector< DoubleVector > position;
		vector< DoubleVector > orientation;
		GeometryType geometry;

		// Auxiliar Functions
		void reservePositionOrientationMemory();
		void reservePropertyMemory();
};

#endif