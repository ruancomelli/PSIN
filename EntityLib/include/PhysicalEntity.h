#ifndef PHYSICAL_ENTITY_H
#define PHYSICAL_ENTITY_H

#include <vector>
#include <stdexcept>

#include <Entity.h>
#include <Vector.h>
#include <Vector3D.h>

using namespace std;


enum GeometryType{
	SPHERE = 0,
	DEFAULT = SPHERE
};

enum ScalarProperty{
	MASS = 0,
	MOMENT_OF_INERTIA,		// J
	VOLUME,
	SPECIFIC_MASS,			// \rho
	DISSIPATIVE_CONSTANT,	// A
	POISSON_RATIO,			// \nu
	ELASTIC_MODULUS,		// E or Y
	TANGENTIAL_DAMPING,		// \gamma^t
	VISCOSITY,				// \mu
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
		PhysicalEntity(const int taylorOrder, const int dimension, const int handle = -1);
		/*PhysicalEntity(const int handle, const vector<double> scalarPropertyVector);
			This is commented because this function seems unnecessary.	*/
		// ---- Spatial localization ----
		void setPosition(const int derivative, const double x, const double y, const double z = 0);
		void setPosition(const int derivative, const Vector3D & vec);
		void setPosition(const vector<Vector3D>  & position);
		vector<Vector3D> getPosition(void) const;
		Vector3D getPosition(const int) const;
		
		void setOrientation(const int derivative, const double x, const double y, const double z);
		void setOrientation(const int derivative, const Vector3D & vec);
		void setOrientation(const vector<Vector3D> & orientation);
		vector<Vector3D> getOrientation(void) const;
		Vector3D getOrientation(const int derivate) const;
		
		// ---- Geometry ----
		void setGeometry(const GeometryType);
		GeometryType getGeometry() const;
		
		// ---- Properties ----
		void setTaylorOrder(const int taylorOrder);
		void setScalarProperty(const int scalarPropertyIdentifier, const double scalarPropertyValue);
		void setScalarProperty(const DoubleVector scalarPropertyVector);
		double getScalarProperty(const int scalarPropertyIdentifier) const;
		DoubleVector getScalarProperty() const;
		
		// ---- Distance ----
		double distance(const PhysicalEntity physicalEntity);
		
	private:
		int taylorOrder; // Number of derivates. If zero, there is just the position (not the velocity)
		static int dimension; // Dimension of simulation. ( = 2 ) or ( = 3 )

		DoubleVector scalarProperty;
		DoubleVector2D vectorialProperty;
		vector < DoubleVector2D > matricialProperty;
		
		vector<Vector3D> position;
		vector<Vector3D> orientation;
		GeometryType geometry;
		
		void reservePositionOrientationMemory(void);
		void reservePropertyMemory(void);
		void setDimension(const int dimension);
};

#endif
